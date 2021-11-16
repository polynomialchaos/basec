/*******************************************************************************
 * @file utils_file.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef UTILS_FILE_H
#define UTILS_FILE_H

#include <stdio.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief Close a given file pointer
 * @param[in] file_ptr
 ******************************************************************************/
void close_file(FILE *file_ptr);

/*******************************************************************************
 * @brief Create a file at the given path
 * @param[in] path
 * @return FILE*
 ******************************************************************************/
FILE *create_file(cstring_t path);

/*******************************************************************************
 * @brief Check if file exists at the given path
 * @param[in] path
 * @return bool_t
 ******************************************************************************/
bool_t file_exists(cstring_t path);

/*******************************************************************************
 * @brief Open a file at the given path
 * @param[in] path
 * @return FILE*
 ******************************************************************************/
FILE *open_file(cstring_t path);

#endif /* UTILS_FILE_H */