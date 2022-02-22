/*******************************************************************************
 * @file memory.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdlib.h>
#include "utils_private.h"

/*******************************************************************************
 * @brief Allocate portion of memory and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] size
 * @return void*
 ******************************************************************************/
void *allocate_pass(cstring_t _file, int _line, cstring_t _function,
                    size_t size)
{
    if (size <= 0)
        return NULL;

    void *ptr = malloc(size);
    CHECK_EXPRESSION_PASS(_file, _line, _function, ptr != NULL);

    return ptr;
}

/*******************************************************************************
 * @brief Deallocate portion of memory
 * @param[in] ptr
 ******************************************************************************/
void deallocate_wo_null(void *ptr)
{
    if (ptr != NULL)
        free(ptr);
}

/*******************************************************************************
 * @brief Reallocate portion of memory and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] old_ptr
 * @param[in] size
 * @return void*
 ******************************************************************************/
void *reallocate_pass(cstring_t _file, int _line, cstring_t _function,
                      void *old_ptr, size_t size)
{
    if (size <= 0)
    {
        if (old_ptr != NULL)
            free(old_ptr);

        return NULL;
    }

    void *ptr = realloc(old_ptr, size);
    CHECK_EXPRESSION_PASS(_file, _line, _function, ptr != NULL);

    return ptr;
}