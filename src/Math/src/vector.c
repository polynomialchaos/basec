/*******************************************************************************
 * @file math_vector.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include "basec/math_module.h"

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
 * @param[out] dest
 * @param[in] n
 ******************************************************************************/
double cos_angle_n(double *a, double *b, size_t n)
{

    double result = dot_n(a, b, n);
    result /= len_n(a, n);
    result /= len_n(b, n);
    result = MAX_T(MIN_T(result, 1.0), -1.0);

    return result;
}

/*******************************************************************************
 * @brief Cosinuns(angle) term of two vectors
 * @param[in] a
 * @param[in] b
 * @param[in] n
 * @return double
 ******************************************************************************/
void copy_n(double *source, double *dest, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        dest[i] = source[i];
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
            return TRUE;

    return FALSE;
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
            return TRUE;

    return FALSE;
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
    double max = -DOUBLE_MAX;

    for (size_t i = 0; i < n; ++i)
        max = MAX_T(max, a[i]);

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
    double min = DOUBLE_MAX;

    for (size_t i = 0; i < n; ++i)
        min = MIN_T(min, a[i]);

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

    if (ABS_T(b[0]) > ABS_T(b[1]))
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
 * @param[out] a
 * @param[in] n
 ******************************************************************************/
void set_value_n(double value, double *a, size_t n)
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