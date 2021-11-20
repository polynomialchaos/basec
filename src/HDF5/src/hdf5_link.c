/*******************************************************************************
 * @file hdf5_link.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "hdf5_private.h"

/*******************************************************************************
 * @brief Wrapper to create a HDF5 soft link
 * @param parent_id
 * @param link_name
 * @param target
 ******************************************************************************/
void create_hdf5_soft_link(hid_t parent_id,
                           cstring_t link_name, cstring_t target)
{
    hid_t plist_id = H5Pcreate(H5P_LINK_CREATE);
    check_hdf5_expression(H5Lcreate_soft(
        target, parent_id, link_name, plist_id, H5P_DEFAULT));
    check_hdf5_expression(H5Pclose(plist_id));
}

/*******************************************************************************
 * @brief Wrapper to delete a HDF5 soft link
 * @param parent_id
 * @param link_name
 ******************************************************************************/
void delete_hdf5_link(hid_t parent_id, cstring_t link_name)
{
    hid_t plist_id = H5Pcreate(H5P_LINK_ACCESS);
    check_hdf5_expression(H5Ldelete(parent_id, link_name, plist_id));
    check_hdf5_expression(H5Pclose(plist_id));
}

/*******************************************************************************
 * @brief Wrapper to check if HDF5 link exists
 * @param parent_id
 * @param link_name
 * @return bool_t
 ******************************************************************************/
bool_t exists_hdf5_link(hid_t parent_id, cstring_t link_name)
{
    int result = H5Lexists(parent_id, link_name, H5P_DEFAULT);
    check_hdf5_expression(result);

    return (result > 0);
}
