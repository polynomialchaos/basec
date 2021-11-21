/*******************************************************************************
 * @file main.c
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
 * @return int
 ******************************************************************************/
int main(int argc, string_t *argv)
{
    mpi_initialize(argc, argv, BFLS, BFLS);

    char *file_name = "test.h5";
    hid_t file_id = open_hdf5_file(file_name);

    char *group_name = "test_group";
    check_expression(exists_hdf5_group(file_id, group_name) == BTRU);
    hid_t group_id = open_hdf5_group(file_id, group_name);

    int scal_int_attr = 0;
    double scal_dbl_attr = 0.0;
    string_t scal_str_attr = NULL;

    get_hdf5_attribute(group_id, "scal_int_attr", HDF5Int, &scal_int_attr);
    check_expression(scal_int_attr == 144);

    get_hdf5_attribute(group_id, "scal_dbl_attr", HDF5Double, &scal_dbl_attr);
    check_expression(scal_dbl_attr == 12.0);

    size_t str_len = get_hdf5_attribute_size(group_id, "scal_str_attr");
    scal_str_attr = ALLOCATE(sizeof(char) * str_len);
    get_hdf5_attribute(group_id, "scal_str_attr", HDF5String, &scal_str_attr);
    check_expression(is_equal(scal_str_attr, "Hello World!"));

    DEALLOCATE(scal_str_attr);

    hsize_t dim = 4;
    int *vec_int_attr = ALLOCATE(sizeof(int) * dim);
    double *vec_dbl_attr = ALLOCATE(sizeof(double) * dim);
    string_t *vec_str_attr = NULL;

    get_hdf5_attribute_n(group_id, "vec_int_attr",
                         HDF5Int, vec_int_attr, dim);
    check_expression(vec_int_attr[0] == 144);
    check_expression(vec_int_attr[1] == 101);
    check_expression(vec_int_attr[2] == 1);
    check_expression(vec_int_attr[3] == 12);

    get_hdf5_attribute_n(group_id, "vec_dbl_attr",
                         HDF5Double, vec_dbl_attr, dim);
    check_expression(vec_dbl_attr[0] == 12.0);
    check_expression(vec_dbl_attr[1] == -3.0);
    check_expression(vec_dbl_attr[2] == 1.0);
    check_expression(vec_dbl_attr[3] == -6.0);

    str_len = get_hdf5_attribute_size(group_id, "vec_str_attr");
    vec_str_attr = allocate_hdf5_string_buffer(dim, str_len, NULL);
    get_hdf5_attribute_n(group_id, "vec_str_attr",
                         HDF5String, vec_str_attr, dim);
    check_expression(is_equal(vec_str_attr[0], "Hello"));
    check_expression(is_equal(vec_str_attr[1], "See you! + World!"));
    check_expression(is_equal(vec_str_attr[2], "a"));
    check_expression(is_equal(vec_str_attr[3], "be"));

    DEALLOCATE(vec_int_attr);
    DEALLOCATE(vec_dbl_attr);
    DEALLOCATE(vec_str_attr);

    close_hdf5_group(group_id);

    // vector dataset
    vec_int_attr = ALLOCATE(sizeof(int) * dim);
    vec_dbl_attr = ALLOCATE(sizeof(double) * dim);
    vec_str_attr = NULL;
    get_hdf5_dataset_n(file_id, "vec_int_dset", HDF5Int, dim, vec_int_attr);
    check_expression(vec_int_attr[0] == 144);
    check_expression(vec_int_attr[1] == 101);
    check_expression(vec_int_attr[2] == 1);
    check_expression(vec_int_attr[3] == 12);

    get_hdf5_dataset_n(file_id, "vec_dbl_dset", HDF5Double, dim, vec_dbl_attr);
    check_expression(vec_dbl_attr[0] == 12.0);
    check_expression(vec_dbl_attr[1] == -3.0);
    check_expression(vec_dbl_attr[2] == 1.0);
    check_expression(vec_dbl_attr[3] == -6.0);

    str_len = get_hdf5_dataset_size(file_id, "vec_str_dset");
    vec_str_attr = allocate_hdf5_string_buffer(dim, str_len, NULL);
    get_hdf5_dataset_n(file_id, "vec_str_dset", HDF5String, dim, vec_str_attr);
    check_expression(is_equal(vec_str_attr[0], "Hello"));
    check_expression(is_equal(vec_str_attr[1], "See you! + World!"));
    check_expression(is_equal(vec_str_attr[2], "a"));
    check_expression(is_equal(vec_str_attr[3], "be"));

    DEALLOCATE(vec_int_attr);
    DEALLOCATE(vec_dbl_attr);
    DEALLOCATE(vec_str_attr);

    // vector dataset + offset/count/stride/block + hyperslab
    hsize_t dim_glob = 20;
    hsize_t offset = 4;
    hsize_t count = dim;
    vec_int_attr = ALLOCATE(sizeof(int) * dim);
    get_hdf5_dataset_chunk_n(file_id, "vec_int_dset_off", HDF5Int,
                             dim, 1, &dim_glob,
                             &offset, &count, NULL, NULL, vec_int_attr);

    hsize_t stride = 2;
    get_hdf5_dataset_chunk_n(file_id, "vec_int_dset_str", HDF5Int,
                             dim, 1, &dim_glob,
                             &offset, &count, &stride, NULL, vec_int_attr);

    count = 2;
    stride = 4;
    hsize_t block = 2;
    get_hdf5_dataset_chunk_n(file_id, "vec_int_dset_blk", HDF5Int,
                             dim, 1, &dim_glob,
                             &offset, &count, &stride, &block, vec_int_attr);

    size_t n_elements = 4;
    hsize_t elements[] = {0, 12, 13, 14};
    get_hdf5_dataset_select_n(file_id, "vec_int_dset_hps", HDF5Int,
                              dim, dim_glob,
                              elements, n_elements, vec_int_attr);

    DEALLOCATE(vec_int_attr);

    // array dataset
    hsize_t dim_arr[] = {4, 6};
    double *arr_dbl_dset = ALLOCATE(sizeof(double) * dim_arr[0] * dim_arr[1]);
    // for (hsize_t i = 0; i < dim_arr[0]; ++i)
    //     for (hsize_t j = 0; j < dim_arr[1]; ++j)
    //         *(arr_dbl_dset + i * dim_arr[1] + j) = i * dim_arr[1] + j + 1;

    get_hdf5_dataset_n_m(file_id, "arr_dbl_dset", HDF5Double,
                         dim_arr, arr_dbl_dset);

    // array dataset + offset/count/stride/block
    hsize_t dim_arr_glob[] = {20, 20};
    hsize_t offset_arr[] = {4, 4};
    hsize_t count_arr[] = {4, 6};
    get_hdf5_dataset_chunk_n_m(file_id, "arr_dbl_dset_off", HDF5Double,
                               dim_arr, 2, dim_arr_glob,
                               offset_arr, count_arr, NULL, NULL,
                               arr_dbl_dset);

    vec_dbl_attr = ALLOCATE(sizeof(double) * dim);
    hsize_t offset_vec[] = {10, 10};
    hsize_t count_vec[] = {1, 4};
    get_hdf5_dataset_chunk_n(file_id, "arr_dbl_dset_off", HDF5Double,
                             dim, 2, dim_arr_glob,
                             offset_vec, count_vec, NULL, NULL,
                             vec_dbl_attr);

    DEALLOCATE(vec_dbl_attr);

    hsize_t stride_arr[] = {2, 2};
    get_hdf5_dataset_chunk_n_m(file_id, "arr_dbl_dset_str", HDF5Double,
                               dim_arr, 2, dim_arr_glob,
                               offset_arr, count_arr, stride_arr, NULL,
                               arr_dbl_dset);

    hsize_t count_blk[] = {2, 3};
    hsize_t stride_blk[] = {4, 4};
    hsize_t block_arr[] = {2, 2};
    get_hdf5_dataset_chunk_n_m(file_id, "arr_dbl_dset_blk", HDF5Double,
                               dim_arr, 2, dim_arr_glob,
                               offset_arr, count_blk, stride_blk, block_arr,
                               arr_dbl_dset);

    hsize_t off_elm = 1;
    size_t n_elements_arr = 4;
    hsize_t elements_arr[] = {0, 1, 2, 3};
    get_hdf5_dataset_select_n_m(file_id, "arr_dbl_dset_hps", HDF5Double,
                                dim_arr, dim_arr_glob,
                                off_elm, elements_arr, n_elements_arr,
                                arr_dbl_dset);

    DEALLOCATE(arr_dbl_dset);

    close_hdf5_file(file_id);

    mpi_finalize();

    return 0;
}