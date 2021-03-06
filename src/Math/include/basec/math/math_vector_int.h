/*******************************************************************************
 * @file math_vector_int.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef MATH_VECTOR_INT_H
#define MATH_VECTOR_INT_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief Copy an integer vector to a other integer vector
 * @param[in] source
 * @param[in] n
 * @param[out] dest
 ******************************************************************************/
void copy_int_n(int *source, size_t n, int *dest);

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
 * @param[in] n
 * @param[out] a
 ******************************************************************************/
void set_value_int_n(int value, size_t n, int *a);

/*******************************************************************************
 * @brief Sum up an integer vector
 * @param[in] a
 * @param[in] n
 * @return int
 ******************************************************************************/
int sum_int_n(int *a, size_t n);

#endif /* MATH_VECTOR_INT_H */