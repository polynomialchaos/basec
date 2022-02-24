/*******************************************************************************
 * @file mpi.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "basec/utils_module.h"
#include "basec/mpi_module.h"

/*******************************************************************************
 * @brief Main function
 * @param argc
 * @param argv
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    mpi_initialize(argc, argv, BC_FALSE, BC_FALSE);

    int i_proc = get_rank_number();
    int result;

    BM_MPI_ALL_REDUCE(MPIInt, MPIMax, &i_proc, &result);
    BM_PRINT("Hello World from #%d (max=%d)\n", i_proc, result);

    mpi_finalize();

    return 0;
}