/*******************************************************************************
 * @file string.c
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
    string_t test_string = allocate_strcpy("Hallo du .....");
    check_expression(test_string != NULL);
    printf_r("%s\n", test_string);

    string_t test_string2 = allocate_strcat("Hallo", " du .....");
    check_expression(test_string2 != NULL);
    printf_r("%s\n", test_string2);

    check_expression(count_chars(test_string2, '.') == 5);

    check_expression(is_digit(test_string2) == FALSE);
    check_expression(is_digit("1.0") == FALSE);
    check_expression(is_digit("1") == TRUE);

    check_expression(is_equal(NULL, NULL) == TRUE);
    check_expression(is_equal(test_string, NULL) == FALSE);
    check_expression(is_equal(NULL, test_string) == FALSE);
    check_expression(is_equal(test_string, test_string2) == TRUE);
    check_expression(is_equal(test_string, "") == FALSE);

    check_expression(is_empty("") == TRUE);
    check_expression(is_empty(NULL) == TRUE);
    check_expression(is_empty(test_string) == FALSE);

    check_expression(is_number(test_string2) == FALSE);
    check_expression(is_number("1.0") == TRUE);
    check_expression(is_number("1.0e-16") == TRUE);
    check_expression(is_number("1") == FALSE);

    check_expression(len_trim(NULL) == 0);
    check_expression(len_trim("") == 0);
    check_expression(len_trim(" Hello ") == 5);

    check_expression(is_equal(l_trim("Hello"), "Hello") == TRUE);
    check_expression(is_equal(l_trim("  Hello"), "Hello") == TRUE);

    test_string = reallocate_strcat(test_string, test_string2);
    check_expression(test_string != NULL);
    printf_r("%s\n", test_string);

    replace(test_string, '.', '_');
    printf_r("%s\n", test_string);
    check_expression(is_equal(test_string,
                              "Hallo du _____Hallo du _____") == TRUE);

    string_t test_string3 = allocate_strcpy("Hello");
    string_t test_string4 = allocate_strcpy("Hello ");
    check_expression(is_equal(r_trim(test_string3), "Hello") == TRUE);
    check_expression(is_equal(r_trim(test_string4), "Hello") == TRUE);

    string_t string_vector[] = {
        test_string, test_string2, test_string3, test_string4
    };
    check_expression(strlen_n(string_vector, 4) == 28);

    string_t test_string5 = allocate_strcpy("Hello");
    string_t test_string6 = allocate_strcpy("Hello  ");
    string_t test_string7 = allocate_strcpy("  Hello");
    check_expression(is_equal(trim(test_string5), "Hello") == TRUE);
    check_expression(is_equal(trim(test_string6), "Hello") == TRUE);
    check_expression(is_equal(trim(test_string7), "Hello") == TRUE);

    DEALLOCATE(test_string);
    DEALLOCATE(test_string2);
    DEALLOCATE(test_string3);
    DEALLOCATE(test_string4);
    DEALLOCATE(test_string5);
    DEALLOCATE(test_string6);
    DEALLOCATE(test_string7);

    return 0;
}