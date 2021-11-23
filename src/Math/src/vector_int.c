/*******************************************************************************
 * @file math_vector_int.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include <limits.h>
#include "math_private.h"

/*******************************************************************************
 * @brief Copy an integer vector to a other integer vector
 * @param[in] source
 * @param[in] n
 * @param[out] dest
 ******************************************************************************/
void copy_int_n(int *source, size_t n, int *dest)
{
    for (size_t i = 0; i < n; ++i)
        dest[i] = source[i];
}

/*******************************************************************************
 * @brief Maximum value in an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int max_int_n(int *a, size_t n)
{
    int max = -INT_MAX;

    for (size_t i = 0; i < n; ++i)
        max = MAX(max, a[i]);

    return max;
}

/*******************************************************************************
 * @brief Minimum value in an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int min_int_n(int *a, size_t n)
{
    int min = INT_MAX;

    for (size_t i = 0; i < n; ++i)
        min = MIN(min, a[i]);

    return min;
}

/*******************************************************************************
 * @brief Set all elements in an integer vector to a value
 * @param[in] value
 * @param[in] n
 * @param[out] a
 ******************************************************************************/
void set_value_int_n(int value, size_t n, int *a)
{
    for (size_t i = 0; i < n; ++i)
        a[i] = value;
}

/*******************************************************************************
 * @brief Sum up an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int sum_int_n(int *a, size_t n)
{
    int sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i];

    return sum;
}