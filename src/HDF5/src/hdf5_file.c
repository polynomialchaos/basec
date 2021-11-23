/*******************************************************************************
 * @file hdf5_file.c
 * @author Florian Eigentler
 * @brief @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/mpi_module.h"
#include "hdf5_private.h"

/*******************************************************************************
 * @brief Wrapper to close a HDF5 file
 * @param file_id
 ******************************************************************************/
void close_hdf5_file(hid_t file_id)
{
    CHECK_HDF5_EXPRESSION(H5Fclose(file_id));
}

/*******************************************************************************
 * @brief Wrapper to create a HDF5 file
 * @param file_name
 * @return hid_t
 ******************************************************************************/
hid_t create_hdf5_file(cstring_t file_name)
{
#ifdef MPI
    hid_t plist_id = H5Pcreate(H5P_FILE_ACCESS);
    CHECK_HDF5_EXPRESSION(H5Pset_fapl_mpio(plist_id, comm, info));
#else
    hid_t plist_id = H5P_DEFAULT;
#endif /* MPI */

    hid_t file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, plist_id);
    CHECK_HDF5_EXPRESSION(file_id);

#ifdef MPI
    CHECK_HDF5_EXPRESSION(H5Pclose(plist_id));
#endif /* MPI */

    return file_id;
}

/*******************************************************************************
 * @brief Check if file is valid HDF5 file
 * @param file_name
 * @return bool_t
 ******************************************************************************/
bool_t is_valid_hdf5_file(cstring_t file_name)
{
    deactivate_hdf5_diag();
    int result = H5Fis_hdf5(file_name);
    activate_hdf5_diag();

    return (result > 0);
}

/*******************************************************************************
 * @brief Wrapper to open a HDF5 file
 * @param file_name
 * @return hid_t
 ******************************************************************************/
hid_t open_hdf5_file(cstring_t file_name)
{

#ifdef MPI
    hid_t plist_id = H5Pcreate(H5P_FILE_ACCESS);
    CHECK_HDF5_EXPRESSION(H5Pset_fapl_mpio(plist_id, comm, info));
#else
    hid_t plist_id = H5P_DEFAULT;
#endif /* MPI */

    hid_t file_id = H5Fopen(file_name, H5F_ACC_RDWR, plist_id);
    CHECK_HDF5_EXPRESSION(file_id);

#ifdef MPI
    CHECK_HDF5_EXPRESSION(H5Pclose(plist_id));
#endif /* MPI */

    return file_id;
}
