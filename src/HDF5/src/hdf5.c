/*******************************************************************************
 * @file hdf5.c
 * @author Florian Eigentler
 * @brief @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include "hdf5_private.h"

/** Temporary storage for old error handler dat */
herr_t (*old_func)(hid_t, void *) = NULL;

/** Temporary storage for client data */
void *old_client_data = NULL;

/*******************************************************************************
 * @brief Activate HDF5 diagnostic output
 ******************************************************************************/
void activate_hdf5_diag()
{
    CHECK_EXPRESSION(old_func != NULL);

    /* Restore previous error handler */
    H5Eset_auto(H5E_DEFAULT, old_func, old_client_data);
}

/*******************************************************************************
 * @brief String buffer for writing HDF5 fixed string length array
 * @param strings
 * @param n
 * @return string_t*
 ******************************************************************************/
string_t *allocate_hdf5_string_buffer(size_t n, size_t length,
                                      string_t *strings)
{
    string_t *cstrings = ALLOCATE(sizeof(string_t) * n);
    cstrings[0] = ALLOCATE(sizeof(char) * n * length);
    for (size_t i = 0; i < n; ++i)
    {
        cstrings[i] = cstrings[0] + i * length;
        memset(cstrings[i], '\0', length);
        if (strings != NULL)
            strcpy(cstrings[i], strings[i]);
    }

    return cstrings;
}

/*******************************************************************************
 * @brief Deactivate HDF5 diagnostic output
 ******************************************************************************/
void deactivate_hdf5_diag()
{
    CHECK_EXPRESSION((old_func == NULL) || (old_client_data == NULL));

    /* Save old error handler */
    H5Eget_auto(H5E_DEFAULT, &old_func, &old_client_data);

    /* Turn off error handling */
    H5Eset_auto(H5E_DEFAULT, NULL, NULL);
}

/*******************************************************************************
 * @brief Deallocate a string buffer
 * @param buffer
 ******************************************************************************/
void deallocate_hdf5_string_buffer(string_t *buffer)
{
    DEALLOCATE(*buffer);
}

/*******************************************************************************
 * @brief Get the HDF5 data type
 * @param type
 * @param id
 * @param function
 * @return hid_t
 ******************************************************************************/
hid_t get_hdf5_data_type(hdf5_type_t type, hid_t id, hid_t_fp_hid_t_t function)
{
    hid_t datatype_id = 0;
    switch (type)
    {
    case HDF5Int:
        datatype_id = H5T_NATIVE_INT;
        break;
    case HDF5Double:
        datatype_id = H5T_NATIVE_DOUBLE;
        break;
    case HDF5String:
        datatype_id = function(id);
        break;
    default:
        LOG_ERROR(HDF5_TYPE_FMT, type);
        break;
    }

    return datatype_id;
}

/*******************************************************************************
 * @brief Get the HDF5 space rank
 * @param dataspace_id
 * @return int
 ******************************************************************************/
int get_hdf5_space_rank(hid_t dataspace_id)
{
    int result = H5Sget_simple_extent_ndims(dataspace_id);
    CHECK_HDF5_EXPRESSION(result);

    return result;
}

/*******************************************************************************
 * @brief Get the HDF5 space dims
 * @param dataspace_id
 * @param dims
 ******************************************************************************/
void get_hdf5_space_dims(hid_t dataspace_id, hsize_t *dims)
{
    CHECK_HDF5_EXPRESSION(H5Sget_simple_extent_dims(dataspace_id, dims, NULL));
}

/*******************************************************************************
 * @brief Check for equal dataspace rank and dimension
 * @param dataspace_id
 * @param rank
 * @param dims
 * @return bool_t
 ******************************************************************************/
bool_t is_dataspace_equals(hid_t dataspace_id, int rank, hsize_t *dims)
{
    int d_rank = get_hdf5_space_rank(dataspace_id);
    if (rank != d_rank)
        return BFLS;

    hsize_t d_dims[d_rank];
    get_hdf5_space_dims(dataspace_id, &d_dims[0]);
    for (int i = 0; i < rank; ++i)
        if (dims[i] != d_dims[i])
            return BFLS;

    return BTRU;
}

/*******************************************************************************
 * @brief Set the HDF5 data type
 * @param type
 * @param rank
 * @param dims
 * @return hid_t
 ******************************************************************************/
hid_t set_hdf5_data_type(hdf5_type_t type, void *data, int rank, hsize_t *dims)
{
#ifdef DEBUG
    UNUSED(rank);
    UNUSED(dims);
#endif
    hid_t datatype_id = 0;
    switch (type)
    {
    case HDF5Int:
        datatype_id = H5T_NATIVE_INT;
        break;
    case HDF5Double:
        datatype_id = H5T_NATIVE_DOUBLE;
        break;
    case HDF5String:
        datatype_id = H5Tcopy(H5T_C_S1);
        CHECK_HDF5_EXPRESSION(datatype_id);
        string_t *strvec = (string_t *)data;
        size_t str_len = strlen_n(strvec, rank > 0 ? dims[0] : 1);
        CHECK_HDF5_EXPRESSION(H5Tset_size(datatype_id, str_len + 1));
        break;
    default:
        LOG_ERROR(HDF5_TYPE_FMT, type);
        break;
    }

    return datatype_id;
}

/*******************************************************************************
 * @brief Hyperslab selection (1D)
 * @param dataspace_id
 * @param elements
 * @param n_elements
 ******************************************************************************/
void select_hdf5_elements_1(hid_t dataspace_id,
                            hsize_t *elements, size_t n_elements)
{
    size_t n_coords = n_elements;
    hsize_t *coords = ALLOCATE(sizeof(hsize_t) * n_coords);

    for (size_t i = 0; i < n_elements; ++i)
        coords[i] = elements[i];

    if (n_coords > 0)
        CHECK_HDF5_EXPRESSION(H5Sselect_elements(
            dataspace_id, H5S_SELECT_SET, n_coords, coords));
    else
        CHECK_HDF5_EXPRESSION(H5Sselect_none(dataspace_id));

    DEALLOCATE(coords);
}

/*******************************************************************************
 * @brief Hyperslab selection (2D)
 * @param dataspace_id
 * @param offset
 * @param count
 * @param elements
 * @param n_elements
 ******************************************************************************/
void select_hdf5_elements_2(hid_t dataspace_id, hsize_t offset,
                            hsize_t count, hsize_t *elements, size_t n_elements)
{
    const int rank = 2;
    size_t n_coords = n_elements * count;
    hsize_t *coords = ALLOCATE(sizeof(hsize_t) * n_coords * rank);

    for (size_t i = 0; i < n_elements; ++i)
        for (hsize_t j = 0; j < count; ++j)
        {
            coords[rank * count * i + rank * j] = elements[i];
            coords[rank * count * i + rank * j + 1] = offset + j;
        }

    if (n_coords > 0)
        CHECK_HDF5_EXPRESSION(H5Sselect_elements(
            dataspace_id, H5S_SELECT_SET, n_coords, coords));
    else
        CHECK_HDF5_EXPRESSION(H5Sselect_none(dataspace_id));

    DEALLOCATE(coords);
}

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
                       hsize_t *elements, size_t n_elements)
{
    if (elements != NULL)
    {
        if (rank == 1)
            select_hdf5_elements_1(dataspace_id, elements, n_elements);
        else if (rank == 2)
            select_hdf5_elements_2(dataspace_id, offset[0],
                                   dim, elements, n_elements);
        else
            LOG_ERROR(HDF5_TYPE_FMT, rank);
    }
    else if ((offset != NULL) && (count != NULL))
    {
        CHECK_HDF5_EXPRESSION(
            H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET,
                                offset, stride, count, block));
    }
}
