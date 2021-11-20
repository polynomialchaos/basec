/*******************************************************************************
 * @file hdf5_module.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef HDF5_DATASET_H
#define HDF5_DATASET_H

#include <hdf5.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"
#include "basec/hdf5/hdf5_type.h"

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset chunk (1D)
 ******************************************************************************/
#define get_hdf5_dataset_chunk_n(parent_id, dataset_name, type, rank, dims,    \
                                 glob_dims, offset, count, stride, block,      \
                                 data)                                         \
    get_hdf5_dataset((parent_id), (dataset_name), (type), (rank), (REF(DIMS)), \
                     (1), (REF(glob_dims)), (offset), (count), (stride),       \
                     (block), (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset chunk (2D)
 ******************************************************************************/
#define get_hdf5_dataset_chunk_n_m(parent_id, dataset_name, type, rank, dims, \
                                   glob_dims, offset, count, stride, block,   \
                                   data)                                      \
    get_hdf5_dataset((parent_id), (dataset_name), (type), (rank), (dims),     \
                     (2), (glob_dims), (offset), (count), (stride), (block),  \
                     (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset (1D)
 ******************************************************************************/
#define get_hdf5_dataset_n(parent_id, dataset_name, type, rank, dims, data)    \
    get_hdf5_dataset((parent_id), (dataset_name), (type), (rank), (REF(DIMS)), \
                     (1), (REF(DIMS)), (NULL), (NULL), (NULL), (NULL),         \
                     (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset (2D)
 ******************************************************************************/
#define get_hdf5_dataset_n_m(parent_id, dataset_name, type, rank, dims, data) \
    get_hdf5_dataset((parent_id), (dataset_name), (type), (rank), (dims),     \
                     (2), (dims), (NULL), (NULL), (NULL), (NULL),             \
                     (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset selection (1D)
 ******************************************************************************/
#define get_hdf5_dataset_select_n(parent_id, dataset_name, type, rank, dims,   \
                                  glob_dims, elements, n_elements, data)       \
    get_hdf5_dataset((parent_id), (dataset_name), (type), (rank), (REF(DIMS)), \
                     (1), (REF(glob_dims)), (NULL), (NULL), (NULL), (NULL),    \
                     (elements), (n_elements), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset selection (2D)
 ******************************************************************************/
#define get_hdf5_dataset_select_n_m(parent_id, dataset_name, type, rank, dims, \
                                    glob_dims, offset, count, elements,        \
                                    n_elements, data)                          \
    get_hdf5_dataset((parent_id), (dataset_name), (type), (rank), (dims),      \
                     (2), (glob_dims), (offset), (count), (NULL), (NULL),      \
                     (elements), (n_elements), (data))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset chunk (1D)
 ******************************************************************************/
#define set_hdf5_dataset_chunk_n(parent_id, dataset_name, type, data, dims, \
                                 glob_dims, offset, count, stride, block)   \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data), (1),      \
                     (REF(dims)), (1), (REF(glob_dims)), (offset),          \
                     (count), (stride), (block), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset chunk (2D)
 ******************************************************************************/
#define set_hdf5_dataset_chunk_n_m(parent_id, dataset_name, type, data, rank, \
                                   dims, glob_dims, offset, count,            \
                                   stride, block)                             \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data), (rank),     \
                     (dims), (2), (glob_dims), (offset), (count), (stride),   \
                     (block), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset (1D)
 ******************************************************************************/
#define set_hdf5_dataset_n(parent_id, dataset_name, type, data, dims)       \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data), (1),      \
                     (REF(dims)), (1), (REF(dims)), (NULL), (NULL), (NULL), \
                     (NULL), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset (2D)
 ******************************************************************************/
#define set_hdf5_dataset_n_m(parent_id, dataset_name, type, data, rank, dims) \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data), (rank),     \
                     (dims), (2), (dims), (NULL), (NULL), (NULL),             \
                     (NULL), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset selection (1D)
 ******************************************************************************/
#define set_hdf5_dataset_select_n(parent_id, dataset_name, type, data, dims, \
                                  glob_dims, elements, n_elements)           \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data), (1),       \
                     (REF(dims)), (1), (REF(glob_dims)), (NULL), (NULL),     \
                     (NULL), (NULL), (elements), (n_elements))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset selection (2D)
 ******************************************************************************/
#define set_hdf5_dataset_select_n_m(parent_id, dataset_name, type, data, rank, \
                                    dims, glob_dims, offset,                   \
                                    elements, n_elements)                      \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data), (rank),      \
                     (dims), (2), (glob_dims), (REF(offset)), (NULL),          \
                     (NULL), (NULL), (elements), (n_elements))

/*******************************************************************************
 * @brief Wrapper to check if HDF5 dataset exists
 * @param parent_id
 * @param dataset_name
 * @return true
 * @return false
 ******************************************************************************/
bool_t exists_hdf5_dataset(hid_t parent_id, cstring_t dataset_name);

/*******************************************************************************
 * @brief Wrapper to get a HDF5 dataset
 * @param parent_id
 * @param dataset_name
 * @param type
 * @param data
 * @param rank
 * @param dims
 * @param glob_rank
 * @param glob_dims
 * @param offset
 * @param count
 * @param stride
 * @param block
 * @param elements
 * @param n_elements
 ******************************************************************************/
void get_hdf5_dataset(hid_t parent_id, cstring_t dataset_name,
                      hdf5_type_t type, int rank, hsize_t *dims,
                      int glob_rank, hsize_t *glob_dims,
                      hsize_t *offset, hsize_t *count, hsize_t *stride,
                      hsize_t *block, hsize_t *elements, size_t n_elements,
                      void *data);

/*******************************************************************************
 * @brief Wrapper to get the HDF5 dataset size
 * @param parent_id
 * @param dataset_name
 * @return size_t
 ******************************************************************************/
size_t get_hdf5_dataset_size(hid_t parent_id, cstring_t dataset_name);

/*******************************************************************************
 * @brief Wrapper to create a HDF5 dataset
 * @param parent_id
 * @param dataset_name
 * @param type
 * @param data
 * @param rank
 * @param dims
 * @param glob_rank
 * @param glob_dims
 * @param offset
 * @param count
 * @param stride
 * @param block
 * @param elements
 * @param n_elements
 ******************************************************************************/
void set_hdf5_dataset(hid_t parent_id, cstring_t dataset_name,
                      hdf5_type_t type, void *data, int rank, hsize_t *dims,
                      int glob_rank, hsize_t *glob_dims,
                      hsize_t *offset, hsize_t *count, hsize_t *stride,
                      hsize_t *block, hsize_t *elements, size_t n_elements);

#endif /* HDF5_DATASET_H */