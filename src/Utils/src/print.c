/*******************************************************************************
 * @file print.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "utils_private.h"

#define UTWD 132 /** Terminal width */
#define UTIN 4   /** Block string title indentation */

FILE *stdout_r = NULL; /** Redirected stdout */

/*******************************************************************************
 * @brief Get the redirected stdout
 * @return FILE*
 ******************************************************************************/
FILE *get_stdout()
{
    return (stdout_r == NULL) ? stdout : stdout_r;
}

/*******************************************************************************
 * @brief Print a separator line without title
 * @param[in] symbol
 ******************************************************************************/
void printf_r_sep(const char symbol)
{
    char tmp[UTWD];
    memset(tmp, symbol, UTWD);
    BM_PRINT("%.*s\n", UTWD, tmp);
}

/*******************************************************************************
 * @brief Print a separator line with title
 * @param[in] symbol
 * @param[in] title
 ******************************************************************************/
void printf_r_sep_title(const char symbol, cstring_t title)
{
    char tmp[UTWD];
    memset(tmp, symbol, UTWD);

    int len_tile = BM_MIN(strlen(title),
                          (size_t)(UTWD - 2 * UTIN));

    BM_PRINT("%.*s %.*s %.*s\n", UTIN - 1, tmp, len_tile, title,
             UTWD - UTIN - len_tile - 1, tmp);
}

/*******************************************************************************
 * @brief Set the redirected stdout
 * @param[in] file_ptr
 ******************************************************************************/
void set_stdout(FILE *file_ptr)
{
    stdout_r = file_ptr;
}