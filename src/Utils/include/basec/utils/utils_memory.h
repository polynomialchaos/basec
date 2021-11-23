/*******************************************************************************
 * @file utils_memory.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef UTILS_MEMORY_H
#define UTILS_MEMORY_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro that allocates a portion of memory
 * and pass file, line, function
 ******************************************************************************/
#define ALLOCATE(size) allocate_pass(__PASS__, (size))

/*******************************************************************************
 * @brief A macro that deallocates a portion of memory
 ******************************************************************************/
#define DEALLOCATE(ptr) (          \
    {                              \
        deallocate_wo_null((ptr)); \
        (ptr) = NULL;              \
    })

/*******************************************************************************
 * @brief A macro that reallocates a portion of memory
 * and pass file, line, function
 ******************************************************************************/
#define REALLOCATE(old, size) reallocate_pass(__PASS__, (old), (size))

/*******************************************************************************
 * @brief Allocate portion of memory and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] size
 * @return void*
 ******************************************************************************/
void *allocate_pass(cstring_t _file, int _line, cstring_t _function,
                    size_t size);

/*******************************************************************************
 * @brief Deallocate portion of memory
 * @param[in] ptr
 ******************************************************************************/
void deallocate_wo_null(void *ptr);

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
                      void *old_ptr, size_t size);

#endif /* UTILS_MEMORY_H */