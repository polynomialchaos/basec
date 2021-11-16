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

    check_expression(EQ_T(min_n(vector_3, 3), 1.0));
    check_expression(EQ_T(max_n(vector_3, 3), 3.0));

    set_value_n(3.0, vector_3, 3);
    check_expression(EQ_T(sum_n(vector_3, 3), 9.0));

    copy_n(vector_2, vector_3, 2);
    check_expression(EQ_T(sum_n(vector_3, 3), 6.0));

    check_expression(EQ_T(dot_n(vector_2, vector_3, 2), 5.0));
    check_expression(EQ_T(len_n(vector_3, 3), sqrt(1 + 4 + 9)));

    vector_2[0] = 1;
    vector_2[1] = 0;
    vector_3[0] = 0;
    vector_3[1] = 1;
    check_expression(EQ_T(rad_to_deg(angle_n(vector_2, vector_3, 2)), 90.0));

    vector_3[0] = 1;
    norm_n(vector_3, 3, vector_3);
    check_expression(EQ_T(len_n(vector_3, 3), 1.0));

    vector_2[0] = 1;
    vector_2[1] = 0;
    vector_3[0] = 0;
    vector_3[1] = 1;
    check_expression(EQ_T(det_2(vector_2, vector_3), 1.0));

    double vector_31[3] = {1.0, 0.0, 0.0};
    double vector_32[3] = {0.0, 1.0, 0.0};
    double vector_33[3] = {0.0, 0.0, 1.0};
    check_expression(EQ_T(det_3(vector_31, vector_32, vector_33), 1.0));

    check_expression(is_nan_n(vector_3, 3) == FALSE);
    check_expression(is_inf_n(vector_3, 3) == FALSE);

    vector_3[0] = NAN;
    check_expression(is_inf_n(vector_3, 3) == FALSE);
    check_expression(is_nan_n(vector_3, 3) == TRUE);

    vector_3[0] = INFINITY;
    check_expression(is_inf_n(vector_3, 3) == TRUE);
    check_expression(is_nan_n(vector_3, 3) == FALSE);

    return 0;
}