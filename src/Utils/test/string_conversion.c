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
    printf_r("%d\n", value_b);

    size_t n = 0;
    bool_t *values_b = NULL;
    string_to_n("[0,1,True,False]", LogicalType, VOID_REF(values_b), &n);
    for (size_t i = 0; i < n - 1; ++i)
        printf_r("%d, ", values_b[i]);
    printf_r("%d\n", values_b[n - 1]);
    DEALLOCATE(values_b);

    int value_i;
    string_to("1234", DigitType, &value_i);
    printf_r("%d\n", value_i);

    int *values_i;
    string_to_n("[1,2,3,4,5,6,7,8,9,10]", DigitType, VOID_REF(values_i), &n);
    for (size_t i = 0; i < n - 1; ++i)
        printf_r("%d, ", values_i[i]);
    printf_r("%d\n", values_i[n - 1]);
    DEALLOCATE(values_i);

    double value_d;
    string_to("1234", NumberType, &value_d);
    printf_r("%e\n", value_d);

    double *values_d = NULL;
    string_to_n("[0,1,2,3,4]", NumberType, VOID_REF(values_d), &n);
    for (size_t i = 0; i < n - 1; ++i)
        printf_r("%e, ", values_d[i]);
    printf_r("%e\n", values_d[n - 1]);
    DEALLOCATE(values_d);

    string_t value_c = NULL;
    char string[] = " 1234      ";
    string_to(trim(&string[0]), StringType, &value_c);
    printf_r("'%s' from '%s'\n", value_c, string);
    DEALLOCATE(value_c);

    string_t *values_c = NULL;
    string_to_n("[Hello, Wolrd      ,   for,you]",
                StringType, VOID_REF(values_c), &n);
    for (size_t i = 0; i < n - 1; ++i)
        printf_r("%s, ", values_c[i]);
    printf_r("%s\n", values_c[n - 1]);
    for (size_t i = 0; i < n; ++i)
        DEALLOCATE(values_c[i]);
    DEALLOCATE(values_c);

    return 0;
}