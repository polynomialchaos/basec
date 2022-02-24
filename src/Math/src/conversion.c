/*******************************************************************************
 * @file math_conversion.c
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
 * @brief Conversion from degrees to radiants
 * @param[in] deg
 * @return double
 ******************************************************************************/
double deg_to_rad(double deg)
{
    return deg * BC_PI / 180.0;
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
    double tmp = log10(BM_MAX(BM_ABS(value), 1));

    return (tmp + sign + 1);
}

/*******************************************************************************
 * @brief Conversion from radiants to degrees
 * @param[in] rad
 * @return double
 ******************************************************************************/
double rad_to_deg(double rad)
{
    return rad * 180.0 / BC_PI;
}
