/*******************************************************************************
 * @file basec_print.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-15
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef BASEC_PRINT_H
#define BASEC_PRINT_H

#include <stdio.h>
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to wrap printf to redirected stdout
 ******************************************************************************/
#define printf_r(format, ...) \
    ({ fprintf((get_stdout()), (format), ##__VA_ARGS__); })

/*******************************************************************************
 * @brief A macro to reset redirected stdout
 ******************************************************************************/
#define reset_stdout() set_stdout(NULL)

/*******************************************************************************
 * @brief A macro to wrap variadic printf to redirected stdout
 ******************************************************************************/
#define vprintf_r(format, arg) \
    ({ vfprintf((get_stdout()), (format), (arg)); })

/*******************************************************************************
 * @brief Get the redirected stdout
 * @return FILE*
 ******************************************************************************/
FILE *get_stdout();

/*******************************************************************************
 * @brief Print a separator line without title
 * @param symbol
 ******************************************************************************/
void printf_r_sep(const char symbol);

/*******************************************************************************
 * @brief Print a separator line with title
 * @param symbol
 * @param title
 ******************************************************************************/
void printf_r_sep_title(const char symbol, cstring_t title);

/*******************************************************************************
 * @brief Set the redirected stdout
 * @param file_ptr
 ******************************************************************************/
void set_stdout(FILE *file_ptr);

#endif /* BASEC_PRINT_H */
