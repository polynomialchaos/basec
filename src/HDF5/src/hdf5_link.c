/*******************************************************************************
 * @file hdf5_link.c
 * @author Florian Eigentler
 * @brief @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
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
    CHECK_HDF5_EXPRESSION(H5Lcreate_soft(
        target, parent_id, link_name, plist_id, H5P_DEFAULT));
    CHECK_HDF5_EXPRESSION(H5Pclose(plist_id));
}

/*******************************************************************************
 * @brief Wrapper to delete a HDF5 soft link
 * @param parent_id
 * @param link_name
 ******************************************************************************/
void delete_hdf5_link(hid_t parent_id, cstring_t link_name)
{
    hid_t plist_id = H5Pcreate(H5P_LINK_ACCESS);
    CHECK_HDF5_EXPRESSION(H5Ldelete(parent_id, link_name, plist_id));
    CHECK_HDF5_EXPRESSION(H5Pclose(plist_id));
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
    CHECK_HDF5_EXPRESSION(result);

    return (result > 0);
}
