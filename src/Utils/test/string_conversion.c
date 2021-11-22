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
    string_to("True", LogicalType, &value_b);
    check_expression(value_b == BTRU);

    string_to("False", LogicalType, &value_b);
    check_expression(value_b == BFLS);

    size_t n = 0;
    bool_t *values_b = NULL;
    string_to_n("[0,1,True,False]", LogicalType, VOID_REF(values_b), &n);
    check_expression(n == 4);
    check_expression(values_b[0] == BFLS);
    check_expression(values_b[1] == BTRU);
    check_expression(values_b[2] == BTRU);
    check_expression(values_b[3] == BFLS);
    DEALLOCATE(values_b);

    int value_i;
    string_to("1234", DigitType, &value_i);
    check_expression(value_i == 1234);

    int *values_i;
    string_to_n("[1,-2,-3,-4,5]", DigitType, VOID_REF(values_i), &n);
    check_expression(n == 5);
    check_expression(values_i[0] == 1);
    check_expression(values_i[1] == -2);
    check_expression(values_i[2] == -3);
    check_expression(values_i[3] == -4);
    check_expression(values_i[4] == 5);
    DEALLOCATE(values_i);

    double value_d;
    string_to("1234", NumberType, &value_d);
    check_expression(value_d == 1234.0);

    double *values_d = NULL;
    string_to_n("[1,-2,-3,-4,5]", NumberType, VOID_REF(values_d), &n);
    check_expression(n == 5);
    check_expression(values_d[0] == 1);
    check_expression(values_d[1] == -2);
    check_expression(values_d[2] == -3);
    check_expression(values_d[3] == -4);
    check_expression(values_d[4] == 5);
    DEALLOCATE(values_d);

    string_t value_c = NULL;
    string_t ref_string = " Hello World!  ";
    string_to(ref_string, StringType, &value_c);
    check_expression(is_equal(value_c, ref_string));
    DEALLOCATE(value_c);

    string_t *values_c = NULL;
    string_t ref_strings = "[Hello, World      ,   !,you]";
    string_to_n(ref_strings, StringType, VOID_REF(values_c), &n);
    check_expression(n == 4);
    check_expression(is_equal(values_c[0], "Hello"));
    check_expression(is_equal(values_c[1], " World      "));
    check_expression(is_equal(values_c[2], "   !"));
    check_expression(is_equal(values_c[3], "you"));
    DEALLOCATE(values_c);

    return 0;
}