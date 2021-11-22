/*******************************************************************************
 * @file hdf5_write.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include "basec/mpi_module.h"
#include "basec/hdf5_module.h"

/*******************************************************************************
 * @brief Main test function
 * @param argc
 * @param argv
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    mpi_initialize(argc, argv, BFLS, BFLS);

    char *file_name = "test.h5";
    hid_t file_id = create_hdf5_file(file_name);

    char *group_name = "test_group";
    CHECK_EXPRESSION(exists_hdf5_group(file_id, group_name) == BFLS);
    hid_t group_id = create_hdf5_group(file_id, group_name);
    CHECK_EXPRESSION(exists_hdf5_group(file_id, group_name) == BTRU);

    int scal_int_attr = 144;
    double scal_dbl_attr = 12.0;
    string_t scal_str_attr = "Hello World!";

    SET_HDF5_ATTRIBUTE(group_id, "scal_int_attr", HDF5Int, &scal_int_attr);
    SET_HDF5_ATTRIBUTE(group_id, "scal_dbl_attr", HDF5Double, &scal_dbl_attr);
    SET_HDF5_ATTRIBUTE(group_id, "scal_str_attr", HDF5String, &scal_str_attr);

    hsize_t dim = 4;
    int vec_int_attr[] = {144, 101, 1, 12};
    double vec_dbl_attr[] = {12.0, -3.0, 1.0, -6.0};
    string_t vec_str_attr[] = {"Hello", "See you! + World!", "a", "be"};

    size_t max_len = strlen_n(vec_str_attr, dim) + 1;
    string_t *tmp = allocate_hdf5_string_buffer(dim, max_len, vec_str_attr);

    SET_HDF5_ATTRIBUTE_N(group_id, "vec_int_attr",
                         HDF5Int, vec_int_attr, dim);
    SET_HDF5_ATTRIBUTE_N(group_id, "vec_dbl_attr",
                         HDF5Double, vec_dbl_attr, dim);
    SET_HDF5_ATTRIBUTE_N(group_id, "vec_str_attr",
                         HDF5String, tmp, dim);

    close_hdf5_group(group_id);

    /* vector dataset */
    SET_HDF5_DATASET_N(file_id, "vec_int_dset", HDF5Int, vec_int_attr, dim);
    SET_HDF5_DATASET_N(file_id, "vec_dbl_dset", HDF5Double, vec_dbl_attr, dim);
    SET_HDF5_DATASET_N(file_id, "vec_str_dset", HDF5String, tmp, dim);

    deallocate_hdf5_string_buffer(tmp);
    DEALLOCATE(tmp);

    /* vector dataset + offset/count/stride/block + hyperslab */
    hsize_t dim_glob = 20;
    hsize_t offset = 4;
    hsize_t count = dim;
    SET_HDF5_DATASET_CHUNK_N(file_id, "vec_int_dset_off", HDF5Int,
                             vec_int_attr, dim, 1, &dim_glob,
                             &offset, &count, NULL, NULL);

    hsize_t stride = 2;
    SET_HDF5_DATASET_CHUNK_N(file_id, "vec_int_dset_str", HDF5Int,
                             vec_int_attr, dim, 1, &dim_glob,
                             &offset, &count, &stride, NULL);

    count = 2;
    stride = 4;
    hsize_t block = 2;
    SET_HDF5_DATASET_CHUNK_N(file_id, "vec_int_dset_blk", HDF5Int,
                             vec_int_attr, dim, 1, &dim_glob,
                             &offset, &count, &stride, &block);

    size_t n_elements = 4;
    hsize_t elements[] = {0, 12, 13, 14};
    SET_HDF5_DATASET_SELECT_N(file_id, "vec_int_dset_hps", HDF5Int,
                              vec_int_attr, dim, dim_glob,
                              elements, n_elements);

    /* array dataset */
    hsize_t dim_arr[] = {4, 6};
    double *arr_dbl_dset = ALLOCATE(sizeof(double) * dim_arr[0] * dim_arr[1]);
    for (hsize_t i = 0; i < dim_arr[0]; ++i)
        for (hsize_t j = 0; j < dim_arr[1]; ++j)
            *(arr_dbl_dset + i * dim_arr[1] + j) = i * dim_arr[1] + j + 1;

    SET_HDF5_DATASET_N_M(file_id, "arr_dbl_dset", HDF5Double,
                         arr_dbl_dset, dim_arr);

    /* array dataset + offset/count/stride/block */
    hsize_t dim_arr_glob[] = {20, 20};
    hsize_t offset_arr[] = {4, 4};
    hsize_t count_arr[] = {4, 6};
    SET_HDF5_DATASET_CHUNK_N_M(file_id, "arr_dbl_dset_off", HDF5Double,
                               arr_dbl_dset, dim_arr, 2, dim_arr_glob,
                               offset_arr, count_arr, NULL, NULL);

    hsize_t offset_vec[] = {10, 10};
    hsize_t count_vec[] = {1, 4};
    SET_HDF5_DATASET_CHUNK_N(file_id, "arr_dbl_dset_off", HDF5Double,
                               vec_dbl_attr, dim, 2, dim_arr_glob,
                               offset_vec, count_vec, NULL, NULL);

    hsize_t stride_arr[] = {2, 2};
    SET_HDF5_DATASET_CHUNK_N_M(file_id, "arr_dbl_dset_str", HDF5Double,
                               arr_dbl_dset, dim_arr, 2, dim_arr_glob,
                               offset_arr, count_arr, stride_arr, NULL);

    hsize_t count_blk[] = {2, 3};
    hsize_t stride_blk[] = {4, 4};
    hsize_t block_arr[] = {2, 2};
    SET_HDF5_DATASET_CHUNK_N_M(file_id, "arr_dbl_dset_blk", HDF5Double,
                               arr_dbl_dset, dim_arr, 2, dim_arr_glob,
                               offset_arr, count_blk, stride_blk, block_arr);

    hsize_t off_elm = 2;
    size_t n_elements_arr = 4;
    hsize_t elements_arr[] = {0, 1, 2, 3};
    SET_HDF5_DATASET_SELECT_N_M(file_id, "arr_dbl_dset_hps", HDF5Double,
                                arr_dbl_dset, dim_arr, dim_arr_glob,
                                off_elm, elements_arr, n_elements_arr);

    DEALLOCATE(arr_dbl_dset);

    close_hdf5_file(file_id);
    CHECK_EXPRESSION(is_valid_hdf5_file(file_name) == BTRU);

    mpi_finalize();

    return 0;
}