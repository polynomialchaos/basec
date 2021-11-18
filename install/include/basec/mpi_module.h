/*******************************************************************************
 * @file mpi_module.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
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
#define mpi_all_reduce(sender, receiver, type, function) \
    mpi_all_reduce_n((sender), (receiver), (1), (type), (function));

/*******************************************************************************
 * @brief A macro to call mpi reduce for scalar
 ******************************************************************************/
#define mpi_reduce(sender, receiver, type, function, rank) \
    mpi_reduce_n((sender), (receiver), (1), (type), (function), (rank));

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
#endif /* MPI */

/*******************************************************************************
 * @brief Get the rank object
 * @return int
 */
int get_rank();

/*******************************************************************************
 * @brief Get the is root object
 * @return bool_t
 */
bool_t is_root();

/*******************************************************************************
 * @brief Get the is parallel object
 * @return bool_t
 */
bool_t is_parallel();

/*******************************************************************************
 * @brief Call mpi all_reduce for vector
 * @param sender
 * @param receiver
 * @param n
 * @param type
 * @param function
 ******************************************************************************/
void mpi_all_reduce_n(const void *sender, void *receiver, int n,
                      mpi_type_t type, mpi_function_t function);

/*******************************************************************************
 * @brief
 ******************************************************************************/
void mpi_barrier();

/*******************************************************************************
 * @brief
 * @param argc
 * @param argv
 ******************************************************************************/
void mpi_initialize(int argc, string_t *argv);

/*******************************************************************************
 * @brief
 ******************************************************************************/
void mpi_finalize();

/*******************************************************************************
 * @brief Call mpi receive
 * @param data
 * @param n
 * @param type
 * @param source
 ******************************************************************************/
void mpi_receive(void *data, int n, mpi_type_t type, int source);

/*******************************************************************************
 * @brief Call mpi reduce for vector
 * @param sender
 * @param receiver
 * @param n
 * @param type
 * @param function
 * @param rank
 ******************************************************************************/
void mpi_reduce_n(const void *sender, void *receiver, int n,
                  mpi_type_t type, mpi_function_t function, int rank);

/*******************************************************************************
 * @brief Call mpi send
 * @param data
 * @param n
 * @param type
 * @param destination
 ******************************************************************************/
void mpi_send(const void *data, int n, mpi_type_t type, int destination);

/*******************************************************************************
 * @brief Call mpi send_receive
 * @param send_buffer
 * @param send_count
 * @param type
 * @param destination
 * @param recv_buffer
 * @param recv_count
 * @param source
 ******************************************************************************/
void mpi_send_receive(void *send_buffer, int send_count,
                      mpi_type_t type, int destination,
                      void *recv_buffer, int recv_count, int source);

/*******************************************************************************
 * @brief Get the n procs object
 * @return int
 */
int n_procs();

#endif /* MPI_MODULE_H */