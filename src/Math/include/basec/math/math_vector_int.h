/*******************************************************************************
 * @file math_vector_int.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef MATH_VECTOR_INT_H
#define MATH_VECTOR_INT_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief Copy an integer vector to a other integer vector
 * @param[in] source
 * @param[out] dest
 * @param[in] n
 ******************************************************************************/
void copy_int_n(int *source, int *dest, size_t n);

/*******************************************************************************
 * @brief Maximum value in an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int max_int_n(int *a, size_t n);

/*******************************************************************************
 * @brief Minimum value in an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int min_int_n(int *a, size_t n);

/*******************************************************************************
 * @brief Set all elements in an integer vector to a value
 * @param[in] value
 * @param[out] a
 * @param[in] n
 ******************************************************************************/
void set_value_int_n(int value, int *a, size_t n);

/*******************************************************************************
 * @brief Sum up an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int sum_int_n(int *a, size_t n);

#endif /* MATH_VECTOR_INT_H */