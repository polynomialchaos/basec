/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/utils_module.h"
#include "basec/mpi_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    mpi_initialize(argc, argv, BFLS, BFLS);

    int i_proc = get_rank_number();
    int result;

    MPI_ALL_REDUCE(MPIInt, MPIMax, &i_proc, &result);
    PRINTF("Hello World from #%d (max=%d)\n", i_proc, result);

    mpi_finalize();

    return 0;
}