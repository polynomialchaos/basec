/*******************************************************************************
 * @file utils_print.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef UTILS_PRINT_H
#define UTILS_PRINT_H

#include <stdio.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to wrap printf to redirected stdout
 ******************************************************************************/
#define BM_PRINT(format, ...) \
    ({ fprintf((get_stdout()), (format), ##__VA_ARGS__); })

/*******************************************************************************
 * @brief A macro to reset redirected stdout
 ******************************************************************************/
#define BM_RESET_STDOUT() set_stdout(NULL)

/*******************************************************************************
 * @brief A macro to wrap variadic printf to redirected stdout
 ******************************************************************************/
#define BM_VPRINT(format, arg) \
    ({ vfprintf((get_stdout()), (format), (arg)); })

/*******************************************************************************
 * @brief Get the redirected stdout
 * @return FILE*
 ******************************************************************************/
FILE *get_stdout();

/*******************************************************************************
 * @brief Print a separator line without title
 * @param[in] symbol
 ******************************************************************************/
void printf_r_sep(const char symbol);

/*******************************************************************************
 * @brief Print a separator line with title
 * @param[in] symbol
 * @param[in] title
 ******************************************************************************/
void printf_r_sep_title(const char symbol, cstring_t title);

/*******************************************************************************
 * @brief Set the redirected stdout
 * @param[in] file_ptr
 ******************************************************************************/
void set_stdout(FILE *file_ptr);

#endif /* UTILS_PRINT_H */
