/*******************************************************************************
 * @file hdf5_private.h
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef HDF5_PRIVATE_H
#define HDF5_PRIVATE_H

#include "basec/hdf5_module.h"

#define HDF5_TYPE_FMT "Unknown HDF5 data type (%d)!" /** Unknown type string */

/*******************************************************************************
 * @brief  A macro to check a HDF5 call
 ******************************************************************************/
#define CHECK_HDF5_EXPRESSION(expression) CHECK_EXPRESSION((expression) >= 0)

typedef hid_t (*hid_t_fp_hid_t_t)(hid_t);

/*******************************************************************************
 * @brief Activate HDF5 diagnostic output
 ******************************************************************************/
void activate_hdf5_diag();

/*******************************************************************************
 * @brief Deactivate HDF5 diagnostic output
 ******************************************************************************/
void deactivate_hdf5_diag();

/*******************************************************************************
 * @brief Get the HDF5 data type
 * @param type
 * @param id
 * @param function
 * @return hid_t
 ******************************************************************************/
hid_t get_hdf5_data_type(hdf5_type_t type, hid_t id, hid_t_fp_hid_t_t function);

/*******************************************************************************
 * @brief Get the HDF5 space dims
 * @param dataspace_id
 * @param dims
 ******************************************************************************/
void get_hdf5_space_dims(hid_t dataspace_id, hsize_t *dims);

/*******************************************************************************
 * @brief Get the HDF5 space rank
 * @param dataspace_id
 * @return int
 ******************************************************************************/
int get_hdf5_space_rank(hid_t dataspace_id);

/*******************************************************************************
 * @brief Check for equal dataspace rank and dimension
 * @param dataspace_id
 * @param rank
 * @param dims
 * @return bool_t
 ******************************************************************************/
bool_t is_dataspace_equals(hid_t dataspace_id, int rank, hsize_t *dims);

/*******************************************************************************
 * @brief Set the HDF5 data type
 * @param type
 * @param rank
 * @param dims
 * @return hid_t
 ******************************************************************************/
hid_t set_hdf5_data_type(hdf5_type_t type, void *data, int rank, hsize_t *dims);

/*******************************************************************************
 * @brief Hyperslab selection (1D)
 * @param dataspace_id
 * @param elements
 * @param n_elements
 ******************************************************************************/
void select_hdf5_elements_1(hid_t dataspace_id,
                            hsize_t *elements, size_t n_elements);

/*******************************************************************************
 * @brief Hyperslab selection (2D)
 * @param dataspace_id
 * @param offset
 * @param count
 * @param elements
 * @param n_elements
 ******************************************************************************/
void select_hdf5_elements_2(hid_t dataspace_id, hsize_t offset, hsize_t count,
                            hsize_t *elements, size_t n_elements);

/*******************************************************************************
 * @brief Select either offset/count/stride/block or hyperslab
 * @param rank
 * @param dims
 * @param dataspace_id
 * @param offset
 * @param count
 * @param stride
 * @param block
 * @param elements
 * @param n_elements
 ******************************************************************************/
void select_hdf5_space(int rank, hsize_t dim, hid_t dataspace_id,
                       hsize_t *offset, hsize_t *count,
                       hsize_t *stride, hsize_t *block,
                       hsize_t *elements, size_t n_elements);

#endif /* HDF5_PRIVATE_H */