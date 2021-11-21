/*******************************************************************************
 * @file hdf5_module.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef HDF5_ATTRIBUTE_H
#define HDF5_ATTRIBUTE_H

#include <hdf5.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"
#include "basec/hdf5/hdf5_type.h"

/*******************************************************************************
 * @brief A macro to get a HDF5 attribute
 ******************************************************************************/
#define get_hdf5_attribute(parent_id, attribute_name, type, data) \
    get_hdf5_attribute_r_d((parent_id), (attribute_name), (type), \
                           (0), (NULL), (data))

/*******************************************************************************
 * @brief A macro to get a HDF5 attribute
 ******************************************************************************/
#define get_hdf5_attribute_n(parent_id, attribute_name, type, data, n) \
    get_hdf5_attribute_r_d((parent_id), (attribute_name), (type),        \
                           (1), (REF(n)), (data))

/*******************************************************************************
 * @brief A macro to se a HDF5 attribute
 ******************************************************************************/
#define set_hdf5_attribute(parent_id, attribute_name, type, data) \
    set_hdf5_attribute_r_d((parent_id), (attribute_name), (type), \
                           (data), (0), (NULL))

/*******************************************************************************
 * @brief A macro to se a HDF5 attribute
 ******************************************************************************/
#define set_hdf5_attribute_n(parent_id, attribute_name, type, data, n) \
    set_hdf5_attribute_r_d((parent_id), (attribute_name), (type),   \
                           (data), (1), (REF(n)))

/*******************************************************************************
 * @brief Wrapper to delete a HDF5 attribute
 * @param parent_id
 * @param attribute_name
 ******************************************************************************/
void delete_hdf5_attribute(hid_t parent_id, cstring_t attribute_name);

/*******************************************************************************
 * @brief Wrapper to check if HDF5 attribute exists
 * @param parent_id
 * @param attribute_name
 * @return true
 * @return false
 ******************************************************************************/
bool_t exists_hdf5_attribute(hid_t parent_id, cstring_t attribute_name);

/*******************************************************************************
* @brief Wrapper to get a HDF5 attribute vector
 * @param parent_id
 * @param attribute_name
 * @param type
 * @param rank
 * @param dims
 * @param data
 ******************************************************************************/
void get_hdf5_attribute_r_d(hid_t parent_id, cstring_t attribute_name,
                            hdf5_type_t type, int rank, hsize_t *dims,
                            void *data);

/*******************************************************************************
* @brief Wrapper to get the HDF5 attribute size
 * @param parent_id
 * @param attribute_name
 * @return size_t
 ******************************************************************************/
size_t get_hdf5_attribute_size(hid_t parent_id, cstring_t attribute_name);

/*******************************************************************************
* @brief Wrapper to rename a HDF5 attribute
 * @param parent_id
 * @param attribute_name
 * @param new_attribute_name
 ******************************************************************************/
void rename_hdf5_attribute(hid_t parent_id, cstring_t attribute_name,
                           cstring_t new_attribute_name);

/*******************************************************************************
 * @brief Wrapper to create a HDF5 attribute
 * @param parent_id
 * @param attribute_name
 * @param type
 * @param data
 * @param rank
 * @param dims
 ******************************************************************************/
void set_hdf5_attribute_r_d(hid_t parent_id, cstring_t attribute_name,
                            hdf5_type_t type, void *data,
                            int rank, hsize_t *dims);

#endif /* HDF5_ATTRIBUTE_H */