/*******************************************************************************
 * @file vector.c
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
    double vector_2[2] = {1.0, 2.0};
    double vector_3[3] = {1.0, 2.0, 3.0};

    BM_CHECK_EXPRESSION(BM_EQ(min_n(vector_3, 3), 1.0));
    BM_CHECK_EXPRESSION(BM_EQ(max_n(vector_3, 3), 3.0));

    set_value_n(3.0, 3, vector_3);
    BM_CHECK_EXPRESSION(BM_EQ(sum_n(vector_3, 3), 9.0));

    copy_n(vector_2, 2, vector_3);
    BM_CHECK_EXPRESSION(BM_EQ(sum_n(vector_3, 3), 6.0));

    BM_CHECK_EXPRESSION(BM_EQ(dot_n(vector_2, vector_3, 2), 5.0));
    BM_CHECK_EXPRESSION(BM_EQ(len_n(vector_3, 3), sqrt(1 + 4 + 9)));

    vector_2[0] = 1;
    vector_2[1] = 0;
    vector_3[0] = 0;
    vector_3[1] = 1;
    BM_CHECK_EXPRESSION(
        BM_EQ(rad_to_deg(angle_n(vector_2, vector_3, 2)), 90.0));

    vector_3[0] = 1;
    norm_n(vector_3, 3, vector_3);
    BM_CHECK_EXPRESSION(BM_EQ(len_n(vector_3, 3), 1.0));

    vector_2[0] = 1;
    vector_2[1] = 0;
    vector_3[0] = 0;
    vector_3[1] = 1;
    BM_CHECK_EXPRESSION(BM_EQ(det_2(vector_2, vector_3), 1.0));

    double vector_31[3] = {1.0, 0.0, 0.0};
    double vector_32[3] = {0.0, 1.0, 0.0};
    double vector_33[3] = {0.0, 0.0, 1.0};
    BM_CHECK_EXPRESSION(BM_EQ(det_3(vector_31, vector_32, vector_33), 1.0));

    BM_CHECK_EXPRESSION(is_nan_n(vector_3, 3) == BC_FALSE);
    BM_CHECK_EXPRESSION(is_inf_n(vector_3, 3) == BC_FALSE);

    vector_3[0] = NAN;
    BM_CHECK_EXPRESSION(is_inf_n(vector_3, 3) == BC_FALSE);
    BM_CHECK_EXPRESSION(is_nan_n(vector_3, 3) == BC_TRUE);

    vector_3[0] = INFINITY;
    BM_CHECK_EXPRESSION(is_inf_n(vector_3, 3) == BC_TRUE);
    BM_CHECK_EXPRESSION(is_nan_n(vector_3, 3) == BC_FALSE);

    return 0;
}