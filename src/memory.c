/*******************************************************************************
 * @file memory.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdlib.h>
#include "basec/basec_module.h"

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
    check_expression_pass(_file, _line, _function, ptr != NULL);

    return ptr;
}

/*******************************************************************************
 * @brief Deallocate portion of memory
 * @param ptr
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
    check_expression_pass(_file, _line, _function, ptr != NULL);

    return ptr;
}