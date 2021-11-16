/*******************************************************************************
 * @file file.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/basec_module.h"

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
    check_expression(file_ptr != NULL);

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
        return TRUE;
    }

    return FALSE;
}

/*******************************************************************************
 * @brief Open a file at the given path
 * @param[in] path
 * @return FILE*
 ******************************************************************************/
FILE *open_file(cstring_t path)
{
    FILE *file_ptr = fopen(path, "r");
    check_expression(file_ptr != NULL);

    return file_ptr;
}