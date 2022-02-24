/*******************************************************************************
 * @file string_conversion.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    bool_t value_b;
    BM_STRING_TO("True", LogicalType, &value_b);
    BM_CHECK_EXPRESSION(value_b == BC_TRUE);

    BM_STRING_TO("False", LogicalType, &value_b);
    BM_CHECK_EXPRESSION(value_b == BC_FALSE);

    size_t n = 0;
    bool_t *values_b = NULL;
    BM_STRING_TO_N("[0,1,True,False]", LogicalType, BM_VOID_REF(values_b), &n);
    BM_CHECK_EXPRESSION(n == 4);
    BM_CHECK_EXPRESSION(values_b[0] == BC_FALSE);
    BM_CHECK_EXPRESSION(values_b[1] == BC_TRUE);
    BM_CHECK_EXPRESSION(values_b[2] == BC_TRUE);
    BM_CHECK_EXPRESSION(values_b[3] == BC_FALSE);
    BM_DEALLOCATE(values_b);

    int value_i;
    BM_STRING_TO("1234", DigitType, &value_i);
    BM_CHECK_EXPRESSION(value_i == 1234);

    int *values_i;
    BM_STRING_TO_N("[1,-2,-3,-4,5]", DigitType, BM_VOID_REF(values_i), &n);
    BM_CHECK_EXPRESSION(n == 5);
    BM_CHECK_EXPRESSION(values_i[0] == 1);
    BM_CHECK_EXPRESSION(values_i[1] == -2);
    BM_CHECK_EXPRESSION(values_i[2] == -3);
    BM_CHECK_EXPRESSION(values_i[3] == -4);
    BM_CHECK_EXPRESSION(values_i[4] == 5);
    BM_DEALLOCATE(values_i);

    double value_d;
    BM_STRING_TO("1234", NumberType, &value_d);
    BM_CHECK_EXPRESSION(value_d == 1234.0);

    double *values_d = NULL;
    BM_STRING_TO_N("[1,-2,-3,-4,5]", NumberType, BM_VOID_REF(values_d), &n);
    BM_CHECK_EXPRESSION(n == 5);
    BM_CHECK_EXPRESSION(values_d[0] == 1);
    BM_CHECK_EXPRESSION(values_d[1] == -2);
    BM_CHECK_EXPRESSION(values_d[2] == -3);
    BM_CHECK_EXPRESSION(values_d[3] == -4);
    BM_CHECK_EXPRESSION(values_d[4] == 5);
    BM_DEALLOCATE(values_d);

    string_t value_c = NULL;
    string_t ref_string = " Hello World!  ";
    BM_STRING_TO(ref_string, StringType, &value_c);
    BM_CHECK_EXPRESSION(is_equal(value_c, ref_string));
    BM_DEALLOCATE(value_c);

    string_t *values_c = NULL;
    string_t ref_strings = "[Hello, World      ,   !,you]";
    BM_STRING_TO_N(ref_strings, StringType, BM_VOID_REF(values_c), &n);
    BM_CHECK_EXPRESSION(n == 4);
    BM_CHECK_EXPRESSION(is_equal(values_c[0], "Hello"));
    BM_CHECK_EXPRESSION(is_equal(values_c[1], " World      "));
    BM_CHECK_EXPRESSION(is_equal(values_c[2], "   !"));
    BM_CHECK_EXPRESSION(is_equal(values_c[3], "you"));
    for (size_t i = 0; i < n; ++i)
        BM_DEALLOCATE(values_c[i]);
    BM_DEALLOCATE(values_c);

    return 0;
}