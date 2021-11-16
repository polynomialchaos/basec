/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include "basec/utils_module.h"
#include "basec/math_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    check_expression(EQ_T(rad_to_deg(deg_to_rad(0.0)), 0.0));
    check_expression(EQ_T(rad_to_deg(deg_to_rad(90.0)), 90.0));
    check_expression(EQ_T(rad_to_deg(deg_to_rad(180.0)), 180.0));
    check_expression(EQ_T(rad_to_deg(deg_to_rad(270.0)), 270.0));
    check_expression(EQ_T(rad_to_deg(deg_to_rad(360.0)), 360.0));
    check_expression(EQ_T(rad_to_deg(deg_to_rad(1024.0)), 1024.0));

    check_expression(EQ_T(integer_string_length(1), 1));
    check_expression(EQ_T(integer_string_length(10), 2));
    check_expression(EQ_T(integer_string_length(99), 2));
    check_expression(EQ_T(integer_string_length(-99), 3));
    check_expression(EQ_T(integer_string_length(100), 3));

    return 0;
}