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
#define GET_HDF5_DATASET_CHUNK_N(parent_id, dataset_name, type,      \
                                 dim, glob_rank, glob_dims,          \
                                 offset, count, stride, block, data) \
    get_hdf5_dataset((parent_id), (dataset_name), (type),            \
                     (1), (REF(dim)), (glob_rank), (glob_dims),      \
                     (offset), (count), (stride), (block), (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset chunk (2D)
 ******************************************************************************/
#define GET_HDF5_DATASET_CHUNK_N_M(parent_id, dataset_name, type,      \
                                   dims, glob_rank, glob_dims,         \
                                   offset, count, stride, block, data) \
    get_hdf5_dataset((parent_id), (dataset_name), (type),              \
                     (2), (dims), (glob_rank), (glob_dims),            \
                     (offset), (count), (stride), (block), (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset (1D)
 ******************************************************************************/
#define GET_HDF5_DATASET_N(parent_id, dataset_name, type, dim, data) \
    get_hdf5_dataset((parent_id), (dataset_name), (type),            \
                     (1), (REF(dim)), (1), (REF(dim)),               \
                     (NULL), (NULL), (NULL), (NULL), (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset (2D)
 ******************************************************************************/
#define GET_HDF5_DATASET_N_M(parent_id, dataset_name, type, dims, data) \
    get_hdf5_dataset((parent_id), (dataset_name), (type),               \
                     (2), (dims), (2), (dims),                          \
                     (NULL), (NULL), (NULL), (NULL), (NULL), (0), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset selection (1D)
 ******************************************************************************/
#define GET_HDF5_DATASET_SELECT_N(parent_id, dataset_name, type,             \
                                  dim, glob_dim, elements, n_elements, data) \
    get_hdf5_dataset((parent_id), (dataset_name), (type),                    \
                     (1), (REF(dim)), (1), (REF(glob_dim)),                  \
                     (NULL), (NULL), (NULL), (NULL),                         \
                     (elements), (n_elements), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 dataset selection (2D)
 ******************************************************************************/
#define GET_HDF5_DATASET_SELECT_N_M(parent_id, dataset_name, type,         \
                                    dims, glob_dims,                       \
                                    offset, elements, n_elements, data)    \
    get_hdf5_dataset((parent_id), (dataset_name), (type),                  \
                     (2), (dims), (2), (glob_dims), (REF(offset)), (NULL), \
                     (NULL), (NULL), (elements), (n_elements), (data))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset chunk (1D)
 ******************************************************************************/
#define SET_HDF5_DATASET_CHUNK_N(parent_id, dataset_name, type, data, \
                                 dim, glob_rank, glob_dims,           \
                                 offset, count, stride, block)        \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data),     \
                     (1), (REF(dim)), (glob_rank), (glob_dims),       \
                     (offset), (count), (stride), (block), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset chunk (2D)
 ******************************************************************************/
#define SET_HDF5_DATASET_CHUNK_N_M(parent_id, dataset_name, type, data, \
                                   dims, glob_rank, glob_dims,          \
                                   offset, count, stride, block)        \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data),       \
                     (2), (dims), (glob_rank), (glob_dims),             \
                     (offset), (count), (stride), (block), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset (1D)
 ******************************************************************************/
#define SET_HDF5_DATASET_N(parent_id, dataset_name, type, data, dim) \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data),    \
                     (1), (REF(dim)), (1), (REF(dim)),               \
                     (NULL), (NULL), (NULL), (NULL), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset (2D)
 ******************************************************************************/
#define SET_HDF5_DATASET_N_M(parent_id, dataset_name, type, data, dims) \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data),       \
                     (2), (dims), (2), (dims),                          \
                     (NULL), (NULL), (NULL), (NULL), (NULL), (0))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset selection (1D)
 ******************************************************************************/
#define SET_HDF5_DATASET_SELECT_N(parent_id, dataset_name, type, data, \
                                  dim, glob_dim, elements, n_elements) \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data),      \
                     (1), (REF(dim)), (1), (REF(glob_dim)),            \
                     (NULL), (NULL), (NULL), (NULL), (elements), (n_elements))

/*******************************************************************************
 * @brief A macro to set a HDF5 dataset selection (2D)
 ******************************************************************************/
#define SET_HDF5_DATASET_SELECT_N_M(parent_id, dataset_name, type, data,   \
                                    dims, glob_dims,                       \
                                    offset, elements, n_elements)          \
    set_hdf5_dataset((parent_id), (dataset_name), (type), (data),          \
                     (2), (dims), (2), (glob_dims), (REF(offset)), (NULL), \
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