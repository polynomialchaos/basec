/*******************************************************************************
 * @file hdf5_group.c
 * @author Florian Eigentler
 * @brief @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "hdf5_private.h"

/*******************************************************************************
 * @brief Wrapper to close a HDF5 group
 * @param group_id
 ******************************************************************************/
void close_hdf5_group(hid_t group_id)
{
    CHECK_HDF5_EXPRESSION(H5Gclose(group_id));
}

/*******************************************************************************
 * @brief Wrapper to create a HDF5 group
 * @param parent_id
 * @param group_name
 * @return hid_t
 ******************************************************************************/
hid_t create_hdf5_group(hid_t parent_id, cstring_t group_name)
{
    hid_t plist_id = H5Pcreate(H5P_GROUP_CREATE);
    hid_t group_id = H5Gcreate(
        parent_id, group_name, H5P_DEFAULT, plist_id, H5P_DEFAULT);
    CHECK_HDF5_EXPRESSION(H5Pclose(plist_id));

    CHECK_HDF5_EXPRESSION(group_id);
    return group_id;
}

/*******************************************************************************
 * @brief Wrapper to check if HDF5 group exists
 * @param parent_id
 * @param group_name
 * @return bool_t
 ******************************************************************************/
bool_t exists_hdf5_group(hid_t parent_id, cstring_t group_name)
{
    htri_t result = H5Lexists(parent_id, group_name, H5P_DEFAULT);
    CHECK_HDF5_EXPRESSION(result);

    return (result > 0);
}

/*******************************************************************************
 * @brief Wrapper to open a HDF5 group
 * @param parent_id
 * @param group_name
 * @return hid_t
 ******************************************************************************/
hid_t open_hdf5_group(hid_t parent_id, cstring_t group_name)
{
    hid_t plist_id = H5Pcreate(H5P_GROUP_ACCESS);
    hid_t group_id = H5Gopen(parent_id, group_name, plist_id);
    CHECK_HDF5_EXPRESSION(H5Pclose(plist_id));

    CHECK_HDF5_EXPRESSION(group_id);
    return group_id;
}
