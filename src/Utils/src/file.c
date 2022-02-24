/*******************************************************************************
 * @file file.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "utils_private.h"

/*******************************************************************************
 * @brief Close a given file pointer
 * @param[in] file_ptr
 ******************************************************************************/
void close_file(FILE *file_ptr)
{
    if (file_ptr == NULL)
        return;

    fclose(file_ptr);
}

/*******************************************************************************
 * @brief Create a file at the given path
 * @param[in] path
 * @return FILE*
 ******************************************************************************/
FILE *create_file(cstring_t path)
{
    FILE *file_ptr = fopen(path, "w");
    BM_CHECK_EXPRESSION(file_ptr != NULL);

    return file_ptr;
}

/*******************************************************************************
 * @brief Check if file exists at the given path
 * @param[in] path
 * @return bool_t
 ******************************************************************************/
bool_t file_exists(cstring_t path)
{
    FILE *file = fopen(path, "r");
    if (file)
    {
        fclose(file);
        return BC_TRUE;
    }

    return BC_FALSE;
}

/*******************************************************************************
 * @brief Open a file at the given path
 * @param[in] path
 * @return FILE*
 ******************************************************************************/
FILE *open_file(cstring_t path)
{
    FILE *file_ptr = fopen(path, "r");
    BM_CHECK_EXPRESSION(file_ptr != NULL);

    return file_ptr;
}