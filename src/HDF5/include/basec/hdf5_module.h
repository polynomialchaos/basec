/*******************************************************************************
 * @file hdf5_module.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef HDF5_MODULE_H
#define HDF5_MODULE_H

#include <hdf5.h>
#include "basec/utils_module.h"
#include "basec/hdf5/hdf5_type.h"
#include "basec/hdf5/hdf5_attribute.h"
#include "basec/hdf5/hdf5_dataset.h"

/*******************************************************************************
 * @brief String buffer for writing HDF5 fixed string length array
 * @param strings
 * @param n
 * @return string_t*
 ******************************************************************************/
string_t *allocate_hdf5_string_buffer(string_t *strings, size_t n);

/*******************************************************************************
 * @brief Wrapper to close a HDF5 file
 * @param file_id
 ******************************************************************************/
void close_hdf5_file(hid_t file_id);

/*******************************************************************************
 * @brief Wrapper to close a HDF5 group
 * @param group_id
 ******************************************************************************/
void close_hdf5_group(hid_t group_id);

/*******************************************************************************
 * @brief Wrapper to create a HDF5 file
 * @param file_name
 * @return hid_t
 ******************************************************************************/
hid_t create_hdf5_file(cstring_t file_name);

/*******************************************************************************
 * @brief Wrapper to create a HDF5 group
 * @param parent_id
 * @param group_name
 * @return hid_t
 ******************************************************************************/
hid_t create_hdf5_group(hid_t parent_id, cstring_t group_name);

/*******************************************************************************
 * @brief Wrapper to create a HDF5 soft link
 * @param parent_id
 * @param link_name
 * @param target
 ******************************************************************************/
void create_hdf5_soft_link(hid_t parent_id,
                           cstring_t link_name, cstring_t target);

/*******************************************************************************
 * @brief Deallocate a string buffer
 * @param buffer
 ******************************************************************************/
void deallocate_hdf5_string_buffer(string_t **buffer);

/*******************************************************************************
 * @brief Wrapper to delete a HDF5 soft link
 * @param parent_id
 * @param link_name
 ******************************************************************************/
void delete_hdf5_link(hid_t parent_id, cstring_t link_name);

/*******************************************************************************
 * @brief Wrapper to check if HDF5 group exists
 * @param parent_id
 * @param group_name
 * @return bool_t
 ******************************************************************************/
bool_t exists_hdf5_group(hid_t parent_id, cstring_t group_name);

/*******************************************************************************
 * @brief Wrapper to check if HDF5 link exists
 * @param parent_id
 * @param link_name
 * @return bool_t
 ******************************************************************************/
bool_t exists_hdf5_link(hid_t parent_id, cstring_t link_name);

/*******************************************************************************
 * @brief Wrapper to check if HDF5 file exists
 * @param file_name
 * @return bool_t
 ******************************************************************************/
bool_t is_valid_hdf5_file(cstring_t file_name);

/*******************************************************************************
 * @brief Wrapper to open a HDF5 file
 * @param file_name
 * @return hid_t
 ******************************************************************************/
hid_t open_hdf5_file(cstring_t file_name);

/*******************************************************************************
 * @brief Wrapper to open a HDF5 group
 * @param parent_id
 * @param group_name
 * @return hid_t
 ******************************************************************************/
hid_t open_hdf5_group(hid_t parent_id, cstring_t group_name);

#endif /* HDF5_MODULE_H */