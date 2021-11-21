/*******************************************************************************
 * @file hdf5_attribute.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "hdf5_private.h"

/*******************************************************************************
 * @brief Wrapper to delete a HDF5 attribute
 * @param parent_id
 * @param attribute_name
 ******************************************************************************/
void delete_hdf5_attribute(hid_t parent_id, cstring_t attribute_name)
{
    check_hdf5_expression(H5Adelete(parent_id, attribute_name));
}

/*******************************************************************************
 * @brief Wrapper to check if HDF5 attribute exists
 * @param parent_id
 * @param attribute_name
 * @return true
 * @return false
 ******************************************************************************/
bool_t exists_hdf5_attribute(hid_t parent_id, cstring_t attribute_name)
{
    int result = H5Aexists(parent_id, attribute_name);
    check_hdf5_expression(result);

    return (result > 0);
}

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
                            void *data)
{
    check_expression(exists_hdf5_attribute(parent_id, attribute_name));

    hid_t attribute_id = H5Aopen(parent_id, attribute_name, H5P_DEFAULT);
    check_hdf5_expression(attribute_id);

    hid_t dataspace_id = 0;
    if (rank < 1)
    {
        dataspace_id = H5Screate(H5S_SCALAR);
        check_hdf5_expression(dataspace_id);
    }
    else
    {
        dataspace_id = H5Screate_simple(rank, dims, NULL);
        check_hdf5_expression(dataspace_id);
    }

    hid_t datatype_id = get_hdf5_data_type(type, attribute_id, H5Aget_type);
    check_expression(datatype_id);

    if (type == HDF5String)
    {
        void *str_data = ((string_t *) data)[0];
        check_hdf5_expression(H5Aread(attribute_id, datatype_id, str_data));
        check_hdf5_expression(H5Tclose(datatype_id));
    }
    else
    {
        check_hdf5_expression(H5Aread(attribute_id, datatype_id, data));
    }

    check_hdf5_expression(H5Sclose(dataspace_id));
    check_hdf5_expression(H5Aclose(attribute_id));
}

/*******************************************************************************
* @brief Wrapper to get the HDF5 attribute size
 * @param parent_id
 * @param attribute_name
 * @return size_t
 ******************************************************************************/
size_t get_hdf5_attribute_size(hid_t parent_id, cstring_t attribute_name)
{
    hid_t attribute_id = H5Aopen(parent_id, attribute_name, H5P_DEFAULT);
    check_hdf5_expression(attribute_id);

    hid_t datatype_id = H5Aget_type(attribute_id);
    check_hdf5_expression(datatype_id);

    size_t size = H5Tget_size(datatype_id);

    check_hdf5_expression(H5Tclose(datatype_id));
    check_hdf5_expression(H5Aclose(attribute_id));

    return size;
}

/*******************************************************************************
* @brief Wrapper to rename a HDF5 attribute
 * @param parent_id
 * @param attribute_name
 * @param new_attribute_name
 ******************************************************************************/
void rename_hdf5_attribute(hid_t parent_id, cstring_t attribute_name,
                           cstring_t new_attribute_name)
{
    check_hdf5_expression(
        H5Arename(parent_id, attribute_name, new_attribute_name));
}

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
                            int rank, hsize_t *dims)
{
    check_expression(!exists_hdf5_attribute(parent_id, attribute_name));

    hid_t dataspace_id = 0;
    if (rank < 1)
    {
        dataspace_id = H5Screate(H5S_SCALAR);
        check_hdf5_expression(dataspace_id);
    }
    else
    {
        dataspace_id = H5Screate_simple(rank, dims, NULL);
        check_hdf5_expression(dataspace_id);
    }

    hid_t datatype_id = set_hdf5_data_type(type, data, rank, dims);
    check_expression(datatype_id);

    hid_t attribute_id = H5Acreate(parent_id, attribute_name,
                                   datatype_id, dataspace_id,
                                   H5P_DEFAULT, H5P_DEFAULT);
    check_hdf5_expression(attribute_id);

    if (type == HDF5String)
    {
        void *str_data = ((string_t *) data)[0];
        check_hdf5_expression(H5Awrite(attribute_id, datatype_id, str_data));
        check_hdf5_expression(H5Tclose(datatype_id));
    }
    else
    {
        check_hdf5_expression(H5Awrite(attribute_id, datatype_id, data));
    }

    check_hdf5_expression(H5Aclose(attribute_id));
    check_hdf5_expression(H5Sclose(dataspace_id));
}
