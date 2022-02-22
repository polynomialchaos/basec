/*******************************************************************************
 * @file send_receive.c
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
 * @brief Wrapper for MPI_Recv
 * @param[in] type
 * @param[in] sender
 * @param[in] n
 * @param[out] data
 ******************************************************************************/
void mpi_receive(mpi_type_t type, int sender, int n, void *data)
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(
        MPI_Recv(data, n, as_mpi_type[type],
                 sender, 0, comm, MPI_STATUS_IGNORE));
#else
#ifdef DEBUG
    UNUSED(type);
    UNUSED(sender);
    UNUSED(n);
    UNUSED(data);
#endif /* DEBUG */
#endif /* MPI */
}

/*******************************************************************************
 * @brief Wrapper for MPI_Send
 * @param[in] type
 * @param[in] receiver
 * @param[in] data
 * @param[in] n
 ******************************************************************************/
void mpi_send(mpi_type_t type, int receiver, const void *data, int n)
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(
        MPI_Send(data, n, as_mpi_type[type], receiver, 0, comm));
#else
#ifdef DEBUG
    UNUSED(type);
    UNUSED(receiver);
    UNUSED(data);
    UNUSED(n);
#endif /* DEBUG */
#endif /* MPI */
}

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
                      int r_n, int sender, void *r_data)
{
#ifdef MPI
    CHECK_MPI_EXPRESSION(
        MPI_Sendrecv(s_data, s_n, as_mpi_type[type],
                     receiver, 0,
                     r_data, r_n, as_mpi_type[type],
                     sender, 0, comm, MPI_STATUS_IGNORE));
#else
#ifdef DEBUG
    UNUSED(type);
    UNUSED(s_data);
    UNUSED(s_n);
    UNUSED(receiver);
    UNUSED(r_n);
    UNUSED(sender);
    UNUSED(r_data);
#endif /* DEBUG */
#endif /* MPI */
}