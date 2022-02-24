/*******************************************************************************
 * @file conversion.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
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
    BM_CHECK_EXPRESSION(BM_EQ(rad_to_deg(deg_to_rad(0.0)), 0.0));
    BM_CHECK_EXPRESSION(BM_EQ(rad_to_deg(deg_to_rad(90.0)), 90.0));
    BM_CHECK_EXPRESSION(BM_EQ(rad_to_deg(deg_to_rad(180.0)), 180.0));
    BM_CHECK_EXPRESSION(BM_EQ(rad_to_deg(deg_to_rad(270.0)), 270.0));
    BM_CHECK_EXPRESSION(BM_EQ(rad_to_deg(deg_to_rad(360.0)), 360.0));
    BM_CHECK_EXPRESSION(BM_EQ(rad_to_deg(deg_to_rad(1024.0)), 1024.0));

    BM_CHECK_EXPRESSION(BM_EQ(integer_string_length(1), 1));
    BM_CHECK_EXPRESSION(BM_EQ(integer_string_length(10), 2));
    BM_CHECK_EXPRESSION(BM_EQ(integer_string_length(99), 2));
    BM_CHECK_EXPRESSION(BM_EQ(integer_string_length(-99), 3));
    BM_CHECK_EXPRESSION(BM_EQ(integer_string_length(100), 3));

    return 0;
}