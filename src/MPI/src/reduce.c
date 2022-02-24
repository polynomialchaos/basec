/*******************************************************************************
 * @file reduce.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <string.h>
#include "basec/utils_module.h"
#include "mpi_private.h"

/*******************************************************************************
 * @brief Wrapper for MPI_Allreduce for vectors
 * @param[in] type
 * @param[in] function
 * @param[in] send
 * @param[in] n
 * @param[out] receive
 ******************************************************************************/
void mpi_all_reduce_n(mpi_type_t type, mpi_function_t function,
                      const void *send, int n, void *receive)
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(
        MPI_Allreduce(send, receive, n, as_mpi_type[type],
                      as_mpi_function[function], comm));
#else
#ifdef DEBUG
    BM_UNUSED(function);
#endif /* DEBUG */
    memcpy(receive, send, as_base_type_size[type] * n);
#endif /* MPI */
}

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
                  const void *send, int n, void *receive)
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(
        MPI_Reduce(send, receive, n, as_mpi_type[type],
                   as_mpi_function[function], rank, comm));
#else
#ifdef DEBUG
    BM_UNUSED(function);
    BM_UNUSED(rank);
#endif /* DEBUG */
    memcpy(receive, send, as_base_type_size[type] * n);
#endif /* MPI */
}