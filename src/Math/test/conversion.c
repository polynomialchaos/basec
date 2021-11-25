/*******************************************************************************
 * @file conversion.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include "basec/utils_module.h"
#include "basec/math_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    CHECK_EXPRESSION(EQ(rad_to_deg(deg_to_rad(0.0)), 0.0));
    CHECK_EXPRESSION(EQ(rad_to_deg(deg_to_rad(90.0)), 90.0));
    CHECK_EXPRESSION(EQ(rad_to_deg(deg_to_rad(180.0)), 180.0));
    CHECK_EXPRESSION(EQ(rad_to_deg(deg_to_rad(270.0)), 270.0));
    CHECK_EXPRESSION(EQ(rad_to_deg(deg_to_rad(360.0)), 360.0));
    CHECK_EXPRESSION(EQ(rad_to_deg(deg_to_rad(1024.0)), 1024.0));

    CHECK_EXPRESSION(EQ(integer_string_length(1), 1));
    CHECK_EXPRESSION(EQ(integer_string_length(10), 2));
    CHECK_EXPRESSION(EQ(integer_string_length(99), 2));
    CHECK_EXPRESSION(EQ(integer_string_length(-99), 3));
    CHECK_EXPRESSION(EQ(integer_string_length(100), 3));

    return 0;
}