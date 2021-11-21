/*******************************************************************************
 * @file hdf5_dataset.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "hdf5_private.h"

/*******************************************************************************
 * @brief Wrapper to check if HDF5 dataset exists
 * @param parent_id
 * @param dataset_name
 * @return true
 * @return false
 ******************************************************************************/
bool_t exists_hdf5_datatset(hid_t parent_id, cstring_t dataset_name)
{
    htri_t result = H5Lexists(parent_id, dataset_name, H5P_DEFAULT);
    check_hdf5_expression(result);

    return (result > 0);
}

/*******************************************************************************
 * @brief Wrapper to get a HDF5 dataset
 * @param parent_id
 * @param dataset_name
 * @param type
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
 * @param data
 *******************************************************************************/
void get_hdf5_dataset(hid_t parent_id, cstring_t dataset_name,
                      hdf5_type_t type, int rank, hsize_t *dims,
                      int glob_rank, hsize_t *glob_dims,
                      hsize_t *offset, hsize_t *count, hsize_t *stride,
                      hsize_t *block, hsize_t *elements, size_t n_elements,
                      void *data)
{
    hid_t plist_id = H5Pcreate(H5P_DATASET_XFER);
    check_hdf5_expression(plist_id);
#ifdef MPI
    check_hdf5_expression(H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE));
#endif /* MPI */

    hid_t dataset_id = H5Dopen(parent_id, dataset_name, H5P_DEFAULT);
    check_hdf5_expression(dataset_id);

    hid_t dataspace_id = H5Dget_space(dataset_id);
    check_hdf5_expression(dataspace_id);

    check_expression(glob_rank == get_hdf5_space_rank(dataspace_id));
    if (glob_dims != NULL)
        check_expression(is_dataspace_equals(dataspace_id, glob_rank, glob_dims));

    hid_t memspace_id = H5Screate_simple(rank, dims, NULL);
    check_hdf5_expression(memspace_id);

    hsize_t sel_count = rank > 1 ? dims[1] : 1;
    select_hdf5_space(glob_rank, sel_count, dataspace_id, offset, count,
                      stride, block, elements, n_elements);

    hid_t datatype_id = get_hdf5_data_type(type, dataset_id, H5Dget_type);
    check_hdf5_expression(datatype_id);

    if (type == HDF5String)
    {
        void *str_data = ((string_t *)data)[0];
        check_hdf5_expression(H5Dread(dataset_id, datatype_id, H5S_ALL, H5S_ALL,
                                      plist_id, str_data));
        check_hdf5_expression(H5Tclose(datatype_id));
    }
    else
    {
        check_hdf5_expression(H5Dread(dataset_id, datatype_id, memspace_id,
                                      dataspace_id, plist_id, data));
    }

    check_hdf5_expression(H5Sclose(memspace_id));
    check_hdf5_expression(H5Sclose(dataspace_id));
    check_hdf5_expression(H5Dclose(dataset_id));
    check_hdf5_expression(H5Pclose(plist_id));
}

/*******************************************************************************
 * @brief Wrapper to get the HDF5 dataset size
 * @param parent_id
 * @param dataset_name
 * @return size_t
 ******************************************************************************/
size_t get_hdf5_dataset_size(hid_t parent_id, cstring_t dataset_name)
{
    hid_t dataset_id = H5Dopen(parent_id, dataset_name, H5P_DEFAULT);
    check_hdf5_expression(dataset_id);

    hid_t datatype_id = H5Dget_type(dataset_id);
    check_hdf5_expression(datatype_id);

    size_t size = H5Tget_size(datatype_id);

    check_hdf5_expression(H5Tclose(datatype_id));
    check_hdf5_expression(H5Dclose(dataset_id));

    return size;
}

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
                      int glob_rank, hsize_t *glob_dims, hsize_t *offset,
                      hsize_t *count, hsize_t *stride, hsize_t *block,
                      hsize_t *elements, size_t n_elements)
{
    hid_t plist_id = H5Pcreate(H5P_DATASET_XFER);
    check_hdf5_expression(plist_id);
#ifdef MPI
    check_hdf5_expression(H5Pset_dxpl_mpio(plist_id, H5FD_MPIO_COLLECTIVE));
#endif /* MPI */

    hid_t dataspace_id = H5Screate_simple(glob_rank, glob_dims, NULL);
    check_hdf5_expression(dataspace_id);

    hid_t memspace_id = H5Screate_simple(rank, dims, NULL);
    check_hdf5_expression(memspace_id);

    hid_t datatype_id = set_hdf5_data_type(type, data, rank, dims);
    check_hdf5_expression(datatype_id);

    hid_t dataset_id = (exists_hdf5_datatset(parent_id, dataset_name))
                           ? H5Dopen(parent_id, dataset_name, H5P_DEFAULT)
                           : H5Dcreate(parent_id, dataset_name, datatype_id,
                                       dataspace_id, H5P_DEFAULT,
                                       H5P_DEFAULT, H5P_DEFAULT);
    check_hdf5_expression(dataset_id);

    hsize_t sel_count = rank > 1 ? dims[1] : 1;
    select_hdf5_space(glob_rank, sel_count, dataspace_id, offset, count,
                      stride, block, elements, n_elements);

    if (type == HDF5String)
    {
        void *str_data = ((string_t *)data)[0];
        check_hdf5_expression(H5Dwrite(dataset_id, datatype_id, H5S_ALL,
                                       H5S_ALL, plist_id, str_data));
        check_hdf5_expression(H5Tclose(datatype_id));
    }
    else
    {
        check_hdf5_expression(H5Dwrite(dataset_id, datatype_id, memspace_id,
                                       dataspace_id, plist_id, data));
    }

    check_hdf5_expression(H5Dclose(dataset_id));
    check_hdf5_expression(H5Sclose(memspace_id));
    check_hdf5_expression(H5Sclose(dataspace_id));
    check_hdf5_expression(H5Pclose(plist_id));
}
