/*******************************************************************************
 * @file vector.c
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
    double vector_2[2] = {1.0, 2.0};
    double vector_3[3] = {1.0, 2.0, 3.0};

    CHECK_EXPRESSION(EQ(min_n(vector_3, 3), 1.0));
    CHECK_EXPRESSION(EQ(max_n(vector_3, 3), 3.0));

    set_value_n(3.0, 3, vector_3);
    CHECK_EXPRESSION(EQ(sum_n(vector_3, 3), 9.0));

    copy_n(vector_2, 2, vector_3);
    CHECK_EXPRESSION(EQ(sum_n(vector_3, 3), 6.0));

    CHECK_EXPRESSION(EQ(dot_n(vector_2, vector_3, 2), 5.0));
    CHECK_EXPRESSION(EQ(len_n(vector_3, 3), sqrt(1 + 4 + 9)));

    vector_2[0] = 1;
    vector_2[1] = 0;
    vector_3[0] = 0;
    vector_3[1] = 1;
    CHECK_EXPRESSION(EQ(rad_to_deg(angle_n(vector_2, vector_3, 2)), 90.0));

    vector_3[0] = 1;
    norm_n(vector_3, 3, vector_3);
    CHECK_EXPRESSION(EQ(len_n(vector_3, 3), 1.0));

    vector_2[0] = 1;
    vector_2[1] = 0;
    vector_3[0] = 0;
    vector_3[1] = 1;
    CHECK_EXPRESSION(EQ(det_2(vector_2, vector_3), 1.0));

    double vector_31[3] = {1.0, 0.0, 0.0};
    double vector_32[3] = {0.0, 1.0, 0.0};
    double vector_33[3] = {0.0, 0.0, 1.0};
    CHECK_EXPRESSION(EQ(det_3(vector_31, vector_32, vector_33), 1.0));

    CHECK_EXPRESSION(is_nan_n(vector_3, 3) == BFLS);
    CHECK_EXPRESSION(is_inf_n(vector_3, 3) == BFLS);

    vector_3[0] = NAN;
    CHECK_EXPRESSION(is_inf_n(vector_3, 3) == BFLS);
    CHECK_EXPRESSION(is_nan_n(vector_3, 3) == BTRU);

    vector_3[0] = INFINITY;
    CHECK_EXPRESSION(is_inf_n(vector_3, 3) == BTRU);
    CHECK_EXPRESSION(is_nan_n(vector_3, 3) == BFLS);

    return 0;
}