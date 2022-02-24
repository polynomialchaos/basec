/*******************************************************************************
 * @file mpi_private.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef MPI_PRIVATE_H
#define MPI_PRIVATE_H

#include "basec/mpi_module.h"

#define MPI_ROOT_ID 0 /* Root processor ID */

#ifdef MPI
/*******************************************************************************
 * @brief A macro to check a MPI call
 ******************************************************************************/
#define CHECK_MPI_EXPRESSION(expression) \
    BM_CHECK_EXPRESSION((expression) == MPI_SUCCESS)
#endif /* MPI */

#ifdef MPI
extern const MPI_Datatype as_mpi_type[];                /** MPI types */
extern const MPI_Op as_mpi_function[_mpi_function_max]; /** MPI functions */
#else
extern const size_t as_base_type_size[]; /** MPI type sizes */
#endif /* MPI */

#endif /* MPI_PRIVATE_H */