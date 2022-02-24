/*******************************************************************************
 * @file mpi_module.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef MPI_MODULE_H
#define MPI_MODULE_H

#ifdef MPI
#include <mpi.h>
#endif /* MPI */

#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to call mpi all_reduce for scalar
 ******************************************************************************/
#define BM_MPI_ALL_REDUCE(type, function, send, receive) \
    mpi_all_reduce_n((type), (function), (send), (1), (receive));

/*******************************************************************************
 * @brief A macro to call mpi reduce for scalar
 ******************************************************************************/
#define BM_MPI_REDUCE(type, function, rank, send, receive) \
    mpi_reduce_n((type), (function), (rank), (send), (1), (receive));

/*******************************************************************************
 * @brief MPI type enumeration
 ******************************************************************************/
typedef enum MPIType
{
    MPIInt,    /** Integer MPI type */
    MPIDouble, /** Double MPI type */
    as_mpi_type_max
} mpi_type_t;

/*******************************************************************************
 * @brief MPI function enumeration
 ******************************************************************************/
typedef enum MPIFunction
{
    MPIMax,     /** Maximum MPI function */
    MPIMin,     /** Minimum MPI function */
    MPILogAnd,  /** Logical And MPI function */
    MPILogOr,   /** Logical Or MPI function */
    MPISum,     /** Sum MPI function */
    MPIProduct, /** Product MPI function */
    _mpi_function_max
} mpi_function_t;

#ifdef MPI
extern MPI_Comm comm; /** MPI communicator */
extern MPI_Info info; /** MPI information */
#endif                /* MPI */

/*******************************************************************************
 * @brief Return the rank number
 * @return int
 ******************************************************************************/
int get_rank_number();

/*******************************************************************************
 * @brief Return the root rank flag (MPI ID = 0)
 * @return bool_t
 ******************************************************************************/
bool_t is_root();

/*******************************************************************************
 * @brief Return the parallel run flag
 * @return bool_t
 ******************************************************************************/
bool_t is_parallel();

/*******************************************************************************
 * @brief Return the number of processors
 * @return int
 ******************************************************************************/
int get_number_of_procs();

/*******************************************************************************
 * @brief Wrapper for MPI_Allreduce for vectors
 * @param[in] type
 * @param[in] function
 * @param[in] send
 * @param[in] n
 * @param[out] receive
 ******************************************************************************/
void mpi_all_reduce_n(mpi_type_t type, mpi_function_t function,
                      const void *send, int n, void *receive);

/*******************************************************************************
 * @brief Wrapper for MPI_Barrier
 ******************************************************************************/
void mpi_barrier();

/*******************************************************************************
 * @brief Wrapper for MPI_Finalize
 ******************************************************************************/
void mpi_finalize();

/*******************************************************************************
 * @brief Wrapper for MPI_Initialize
 * @param[in] argc
 * @param[in] argv
 * @param[in] only_rank
 * @param[in] file_out
 ******************************************************************************/
void mpi_initialize(int argc, string_t *argv,
                    bool_t only_rank, bool_t file_out);

/*******************************************************************************
 * @brief Wrapper for MPI_Recv
 * @param[in] type
 * @param[in] sender
 * @param[in] n
 * @param[out] data
 ******************************************************************************/
void mpi_receive(mpi_type_t type, int sender, int n, void *data);

/*******************************************************************************
 * @brief Wrapper for MPI_Reduce for vectors
 * @param[in] type
 * @param[in] function
 * @param[in] rank
 * @param[in] send
 * @param[in] n
 * @param[out] receive
 ******************************************************************************/
void mpi_reduce_n(mpi_type_t type, mpi_function_t function, int rank,
                  const void *send, int n, void *receive);

/*******************************************************************************
 * @brief Wrapper for MPI_Send
 * @param[in] type
 * @param[in] receiver
 * @param[in] data
 * @param[in] n
 ******************************************************************************/
void mpi_send(mpi_type_t type, int receiver, const void *data, int n);

/*******************************************************************************
 * @brief Wrapper for MPI_Sendrecv
 * @param[in] type
 * @param[in] s_data
 * @param[in] s_n
 * @param[in] receiver
 * @param[in] r_n
 * @param[in] sender
 * @param[out] r_data
 ******************************************************************************/
void mpi_send_receive(mpi_type_t type,
                      void *s_data, int s_n, int receiver,
                      int r_n, int sender, void *r_data);

#endif /* MPI_MODULE_H */