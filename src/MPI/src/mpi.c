/*******************************************************************************
 * @file mpi.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/utils_module.h"
#include "mpi_private.h"

int i_mpi_proc = 0;           /* Processor ID */
int n_mpi_procs = 1;          /* Number of MPI processors */
bool_t store_file_out = BTRU; /** Store file out setting */

#ifdef MPI
MPI_Comm comm = MPI_COMM_WORLD; /** MPI communicator */
MPI_Info info = MPI_INFO_NULL;  /** MPI information */

/** MPI types */
const MPI_Datatype as_mpi_type[as_mpi_type_max] = {
    MPI_INT, MPI_DOUBLE};

/** MPI functions */
const MPI_Op as_mpi_function[_mpi_function_max] = {
    MPI_MAX, MPI_MIN, MPI_LAND, MPI_LOR, MPI_SUM, MPI_PROD};
#else
/** MPI type sizes */
const size_t as_base_type_size[as_mpi_type_max] = {
    sizeof(int), sizeof(double)};
#endif /* MPI */

/*******************************************************************************
 * @brief Return the rank number
 * @return int
 ******************************************************************************/
int get_rank_number()
{
    return i_mpi_proc;
}

/*******************************************************************************
 * @brief Return the root rank flag (MPI ID = 0)
 * @return bool_t
 ******************************************************************************/
bool_t is_root()
{
    return (i_mpi_proc == MPI_ROOT_ID);
}

/*******************************************************************************
 * @brief Return the parallel run flag
 * @return bool_t
 ******************************************************************************/
bool_t is_parallel()
{
    return (n_mpi_procs > 1);
}

/*******************************************************************************
 * @brief Return the number of processors
 * @return int
 ******************************************************************************/
int get_number_of_procs()
{
    return n_mpi_procs;
}

/*******************************************************************************
 * @brief Global error state handler for MPI runs
 ******************************************************************************/
void global_error_handler_mpi()
{
    int tmp = is_active_error();
    MPI_ALL_REDUCE(MPIInt, MPILogOr, &tmp, &tmp);
    set_global_error(tmp);
}

/*******************************************************************************
 * @brief Wrapper for MPI_Barrier
 ******************************************************************************/
void mpi_barrier()
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(MPI_Barrier(comm));
#endif /* MPI */
}

/*******************************************************************************
 * @brief Wrapper for MPI_Finalize
 ******************************************************************************/
void mpi_finalize()
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(MPI_Finalize());

    RESET_GLOBAL_ERROR_STATE_HANDLER();

    if (is_parallel() && !is_root())
    {
        close_file(get_stdout());
        RESET_STDOUT();
    }
#endif /* MPI */
}

/*******************************************************************************
 * @brief Wrapper for MPI_Initialize
 * @param[in] argc
 * @param[in] argv
 * @param[in] only_rank
 * @param[in] file_out
 ******************************************************************************/
void mpi_initialize(int argc, string_t *argv,
                    bool_t only_rank, bool_t file_out)
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(MPI_Init(&argc, &argv));
    CHECK_MPI_EXPRESSION(MPI_Comm_rank(comm, &i_mpi_proc));
    CHECK_MPI_EXPRESSION(MPI_Comm_size(comm, &n_mpi_procs));

    set_global_error_state_handler(global_error_handler_mpi);
    store_file_out = file_out;

    if (is_parallel() && !is_root())
    {
        if (only_rank)
        {
            set_stdout(create_file("/dev/null"));
        }
        else if (store_file_out)
        {
            string_t file_path = ALLOCATE(sizeof(char) * 255);
            sprintf(file_path, "stdout_proc_%d.log", i_mpi_proc);
            set_stdout(create_file(file_path));
            DEALLOCATE(file_path);
        }
    }
#else
#ifdef DEBUG
    UNUSED(argc);
    UNUSED(argv);
    UNUSED(only_rank);
    UNUSED(file_out);
#endif /* DEBUG */
#endif /* MPI */
}