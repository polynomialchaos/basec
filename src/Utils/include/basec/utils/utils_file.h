/*******************************************************************************
 * @file utils_file.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
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