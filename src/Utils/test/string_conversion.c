/*******************************************************************************
 * @file string_conversion.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    bool_t value_b;
    STRING_TO("True", LogicalType, &value_b);
    CHECK_EXPRESSION(value_b == BTRU);

    STRING_TO("False", LogicalType, &value_b);
    CHECK_EXPRESSION(value_b == BFLS);

    size_t n = 0;
    bool_t *values_b = NULL;
    STRING_TO_N("[0,1,True,False]", LogicalType, VOID_REF(values_b), &n);
    CHECK_EXPRESSION(n == 4);
    CHECK_EXPRESSION(values_b[0] == BFLS);
    CHECK_EXPRESSION(values_b[1] == BTRU);
    CHECK_EXPRESSION(values_b[2] == BTRU);
    CHECK_EXPRESSION(values_b[3] == BFLS);
    DEALLOCATE(values_b);

    int value_i;
    STRING_TO("1234", DigitType, &value_i);
    CHECK_EXPRESSION(value_i == 1234);

    int *values_i;
    STRING_TO_N("[1,-2,-3,-4,5]", DigitType, VOID_REF(values_i), &n);
    CHECK_EXPRESSION(n == 5);
    CHECK_EXPRESSION(values_i[0] == 1);
    CHECK_EXPRESSION(values_i[1] == -2);
    CHECK_EXPRESSION(values_i[2] == -3);
    CHECK_EXPRESSION(values_i[3] == -4);
    CHECK_EXPRESSION(values_i[4] == 5);
    DEALLOCATE(values_i);

    double value_d;
    STRING_TO("1234", NumberType, &value_d);
    CHECK_EXPRESSION(value_d == 1234.0);

    double *values_d = NULL;
    STRING_TO_N("[1,-2,-3,-4,5]", NumberType, VOID_REF(values_d), &n);
    CHECK_EXPRESSION(n == 5);
    CHECK_EXPRESSION(values_d[0] == 1);
    CHECK_EXPRESSION(values_d[1] == -2);
    CHECK_EXPRESSION(values_d[2] == -3);
    CHECK_EXPRESSION(values_d[3] == -4);
    CHECK_EXPRESSION(values_d[4] == 5);
    DEALLOCATE(values_d);

    string_t value_c = NULL;
    string_t ref_string = " Hello World!  ";
    STRING_TO(ref_string, StringType, &value_c);
    CHECK_EXPRESSION(is_equal(value_c, ref_string));
    DEALLOCATE(value_c);

    string_t *values_c = NULL;
    string_t ref_strings = "[Hello, World      ,   !,you]";
    STRING_TO_N(ref_strings, StringType, VOID_REF(values_c), &n);
    CHECK_EXPRESSION(n == 4);
    CHECK_EXPRESSION(is_equal(values_c[0], "Hello"));
    CHECK_EXPRESSION(is_equal(values_c[1], " World      "));
    CHECK_EXPRESSION(is_equal(values_c[2], "   !"));
    CHECK_EXPRESSION(is_equal(values_c[3], "you"));
    DEALLOCATE(values_c);

    return 0;
}