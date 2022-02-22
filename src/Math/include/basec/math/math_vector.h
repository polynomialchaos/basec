/*******************************************************************************
 * @file math_vector.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief Angle between two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
double angle_n(double *a, double *b, size_t n);

/*******************************************************************************
 * @brief Copy a vector to a other vector
 * @param[in] source
 * @param[in] n
 * @param[out] dest
 ******************************************************************************/
void copy_n(double *source, size_t n, double *dest);

/*******************************************************************************
 * @brief Cosinuns(angle) term of two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
double cos_angle_n(double *a, double *b, size_t n);

/*******************************************************************************
 * @brief Cross product of two 3D vectors
 * @param[in] a
 * @param[in] b
 * @param[out] c
 ******************************************************************************/
void cross_product_3(double *a, double *b, double *c);

/*******************************************************************************
 * @brief Determinant of 2D Array (two columns)
 * @param[in] a
 * @param[in] b
 * @return double
 ******************************************************************************/
double det_2(double *a, double *b);

/*******************************************************************************
 * @brief Determinant of 3D Array (three columns)
 * @param[in] a
 * @param[in] b
 * @param[in] c
 * @return double
 ******************************************************************************/
double det_3(double *a, double *b, double *c);

/*******************************************************************************
 * @brief Dot product of two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
double dot_n(double *a, double *b, size_t n);

/*******************************************************************************
 * @brief Check for Inf values in vector
 * @param[in] a
 * @param[in] n
 * @return bool_t
 ******************************************************************************/
bool_t is_inf_n(double *a, size_t n);

/*******************************************************************************
 * @brief Check for NaN values in vector
 * @param[in] a
 * @param[in] n
 * @return bool_t
 ******************************************************************************/
bool_t is_nan_n(double *a, size_t n);

/*******************************************************************************
 * @brief Length of vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double len_n(double *a, size_t n);

/*******************************************************************************
 * @brief Maximum value in a vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double max_n(double *a, size_t n);

/*******************************************************************************
 * @brief Minimum value in a vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double min_n(double *a, size_t n);

/*******************************************************************************
 * @brief Euclidean norm of vector
 * @param[in] a
 * @param[in] n
 * @param[out] b
 ******************************************************************************/
void norm_n(double *a, size_t n, double *b);

/*******************************************************************************
 * @brief Orthonormal basis for one 3D vector
 * @param[in] a
 * @param[out] b
 * @param[out] c
 * @param[out] d
 ******************************************************************************/
void orthonormal_basis_3(double *a, double *b, double *c, double *d);

/*******************************************************************************
 * @brief Set all elements in a vector to a value
 * @param[in] value
 * @param[in] n
 * @param[out] a
 ******************************************************************************/
void set_value_n(double value, size_t n, double *a);

/*******************************************************************************
 * @brief Sum up a vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double sum_n(double *a, size_t n);

#endif /* MATH_VECTOR_H */