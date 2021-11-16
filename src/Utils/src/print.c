/*******************************************************************************
 * @file print.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "utils_private.h"

#define TERM_WIDTH 132 /** Terminal width */
#define TITLE_INT 4    /** Block string title indentation */

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
 * @param symbol
 ******************************************************************************/
void printf_r_sep(const char symbol)
{
    char tmp[TERM_WIDTH];
    memset(tmp, symbol, TERM_WIDTH);
    printf_r("%.*s\n", TERM_WIDTH, tmp);
}

/*******************************************************************************
 * @brief Print a separator line with title
 * @param symbol
 * @param title
 ******************************************************************************/
void printf_r_sep_title(const char symbol, cstring_t title)
{
    char tmp[TERM_WIDTH];
    memset(tmp, symbol, TERM_WIDTH);

    int len_tile = MIN_T(strlen(title),
                         (size_t)(TERM_WIDTH - 2 * TITLE_INT));

    printf_r("%.*s %.*s %.*s\n", TITLE_INT - 1, tmp, len_tile, title,
             TERM_WIDTH - TITLE_INT - len_tile - 1, tmp);
}

/*******************************************************************************
 * @brief Set the redirected stdout
 * @param file_ptr
 ******************************************************************************/
void set_stdout(FILE *file_ptr)
{
    stdout_r = file_ptr;
}