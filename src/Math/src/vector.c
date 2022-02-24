/*******************************************************************************
 * @file math_vector.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <math.h>
#include "math_private.h"

/*******************************************************************************
 * @brief Angle between two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
double angle_n(double *a, double *b, size_t n)
{
    return acos(cos_angle_n(a, b, n));
}

/*******************************************************************************
 * @brief Copy a vector to a other vector
 * @param[in] source
 * @param[in] n
 * @param[out] dest
 ******************************************************************************/
void copy_n(double *source, size_t n, double *dest)
{
    for (size_t i = 0; i < n; ++i)
        dest[i] = source[i];
}

/*******************************************************************************
 * @brief Cosinuns(angle) term of two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
double cos_angle_n(double *a, double *b, size_t n)
{
    double result = dot_n(a, b, n);
    result /= len_n(a, n);
    result /= len_n(b, n);
    result = BM_MAX(BM_MIN(result, 1.0), -1.0);

    return result;
}

/*******************************************************************************
 * @brief Cross product of two 3D vectors
 * @param[in] a
 * @param[in] b
 * @param[out] c
 ******************************************************************************/
void cross_product_3(double *a, double *b, double *c)
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

/*******************************************************************************
 * @brief Determinant of 2D Array (two columns)
 * @param[in] a
 * @param[in] b
 * @return double
 ******************************************************************************/
double det_2(double *a, double *b)
{
    return a[0] * b[1] - a[1] * b[0];
}

/*******************************************************************************
 * @brief Determinant of 3D Array (three columns)
 * @param[in] a
 * @param[in] b
 * @param[in] c
 * @return double
 ******************************************************************************/
double det_3(double *a, double *b, double *c)
{
    return a[0] * b[1] * c[2] + a[1] * b[2] * c[0] +
           a[2] * b[0] * c[1] - a[2] * b[1] * c[0] -
           a[0] * b[2] * c[1] - a[1] * b[0] * c[2];
}

/*******************************************************************************
 * @brief Dot product of two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
double dot_n(double *a, double *b, size_t n)
{
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i] * b[i];

    return sum;
}

/*******************************************************************************
 * @brief Check for Inf values in vector
 * @param[in] a
 * @param[in] n
 * @return bool_t
 ******************************************************************************/
bool_t is_inf_n(double *a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (isinf(a[i]))
            return BC_TRUE;

    return BC_FALSE;
}

/*******************************************************************************
 * @brief Check for NaN values in vector
 * @param[in] a
 * @param[in] n
 * @return bool_t
 ******************************************************************************/
bool_t is_nan_n(double *a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (isnan(a[i]))
            return BC_TRUE;

    return BC_FALSE;
}

/*******************************************************************************
 * @brief Length of vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double len_n(double *a, size_t n)
{
    return sqrt(dot_n(a, a, n));
}

/*******************************************************************************
 * @brief Maximum value in a vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double max_n(double *a, size_t n)
{
    double max = -BC_DMAX;

    for (size_t i = 0; i < n; ++i)
        max = BM_MAX(max, a[i]);

    return max;
}

/*******************************************************************************
 * @brief Minimum value in a vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double min_n(double *a, size_t n)
{
    double min = BC_DMAX;

    for (size_t i = 0; i < n; ++i)
        min = BM_MIN(min, a[i]);

    return min;
}

/*******************************************************************************
 * @brief Euclidean norm of vector
 * @param[in] a
 * @param[in] n
 * @param[out] b
 ******************************************************************************/
void norm_n(double *a, size_t n, double *b)
{
    double length = len_n(a, n);
    for (size_t i = 0; i < n; ++i)
        b[i] = a[i] / length;
}

/*******************************************************************************
 * @brief Orthonormal basis for one 3D vector
 * @param[in] a
 * @param[out] b
 * @param[out] c
 * @param[out] d
 ******************************************************************************/
void orthonormal_basis_3(double *a, double *b, double *c, double *d)
{
    norm_n(a, 3, b);

    if (BM_ABS(b[0]) > BM_ABS(b[1]))
    {
        c[0] = -b[2];
        c[1] = 0.0;
        c[2] = b[0];
    }
    else
    {
        c[0] = 0.0;
        c[1] = -b[2];
        c[2] = b[1];
    }

    norm_n(c, 3, c);
    cross_product_3(b, c, d);
    norm_n(d, 3, d);
}

/*******************************************************************************
 * @brief Set all elements in a vector to a value
 * @param[in] value
 * @param[in] n
 * @param[out] a
 ******************************************************************************/
void set_value_n(double value, size_t n, double *a)
{
    for (size_t i = 0; i < n; ++i)
        a[i] = value;
}

/*******************************************************************************
 * @brief Sum up a vector
 * @param[in] a
 * @param[in] n
 * @return double
 ******************************************************************************/
double sum_n(double *a, size_t n)
{
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
        sum += a[i];

    return sum;
}