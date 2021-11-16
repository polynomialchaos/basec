/*******************************************************************************
 * @file math_conversion.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include "math_private.h"

/*******************************************************************************
 * @brief Conversion from degrees to radiants
 * @param[in] deg
 * @return double
 ******************************************************************************/
double deg_to_rad(double deg)
{
    return deg * PI / 180.0;
}

/*******************************************************************************
 * @brief String legth for an integer value
 * @param[in] value
 * @return int
 ******************************************************************************/
int integer_string_length(int value);
int integer_string_length(int value)
{
    int sign = (value < 0.0) ? 1 : 0;
    double tmp = log10(MAX_T(ABS_T(value), 1));

    return (tmp + sign + 1);
}

/*******************************************************************************
 * @brief Conversion from radiants to degrees
 * @param[in] rad
 * @return double
 ******************************************************************************/
double rad_to_deg(double rad)
{
    return rad * 180.0 / PI;
}
