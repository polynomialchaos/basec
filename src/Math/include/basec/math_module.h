/*******************************************************************************
 * @file math_module.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef MATH_MODULE_H
#define MATH_MODULE_H

#include "basec/math/math_bicgstab_gmres.h"
#include "basec/math/math_vector_int.h"
#include "basec/math/math_vector.h"

#define MCPI 3.14159265358979323846 /* MCPI constant */

/*******************************************************************************
 * @brief Conversion from degrees to radiants
 * @param[in] deg
 * @return double
 ******************************************************************************/
double deg_to_rad(double deg);

/*******************************************************************************
 * @brief Return the factorial of a value
 * @param[in] n
 * @return int
 ******************************************************************************/
int factorial(int n);

/*******************************************************************************
 * @brief String legth for an integer value
 * @param[in] value
 * @return int
 ******************************************************************************/
int integer_string_length(int value);

/*******************************************************************************
 * @brief Conversion from radiants to degrees
 * @param[in] rad
 * @return double
 ******************************************************************************/
double rad_to_deg(double rad);

#endif /* MATH_MODULE_H */