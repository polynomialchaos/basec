/*******************************************************************************
 * @file string.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
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
    CHECK_EXPRESSION(test_string != NULL);
    PRINTF("%s\n", test_string);

    string_t test_string2 = allocate_strcat("Hallo", " du .....");
    CHECK_EXPRESSION(test_string2 != NULL);
    PRINTF("%s\n", test_string2);

    CHECK_EXPRESSION(count_chars(test_string2, '.') == 5);

    CHECK_EXPRESSION(is_digit(test_string2) == BFLS);
    CHECK_EXPRESSION(is_digit("1.0") == BFLS);
    CHECK_EXPRESSION(is_digit("1") == BTRU);

    CHECK_EXPRESSION(is_equal(NULL, NULL) == BTRU);
    CHECK_EXPRESSION(is_equal(test_string, NULL) == BFLS);
    CHECK_EXPRESSION(is_equal(NULL, test_string) == BFLS);
    CHECK_EXPRESSION(is_equal(test_string, test_string2) == BTRU);
    CHECK_EXPRESSION(is_equal(test_string, "") == BFLS);

    CHECK_EXPRESSION(is_empty("") == BTRU);
    CHECK_EXPRESSION(is_empty(NULL) == BTRU);
    CHECK_EXPRESSION(is_empty(test_string) == BFLS);

    CHECK_EXPRESSION(is_number(test_string2) == BFLS);
    CHECK_EXPRESSION(is_number("1.0") == BTRU);
    CHECK_EXPRESSION(is_number("1.0e-16") == BTRU);
    CHECK_EXPRESSION(is_number("1") == BFLS);

    CHECK_EXPRESSION(len_trim(NULL) == 0);
    CHECK_EXPRESSION(len_trim("") == 0);
    CHECK_EXPRESSION(len_trim(" Hello ") == 5);

    CHECK_EXPRESSION(is_equal(l_trim("Hello"), "Hello") == BTRU);
    CHECK_EXPRESSION(is_equal(l_trim("  Hello"), "Hello") == BTRU);

    test_string = reallocate_strcat(test_string, test_string2);
    CHECK_EXPRESSION(test_string != NULL);
    PRINTF("%s\n", test_string);

    replace(test_string, '.', '_');
    PRINTF("%s\n", test_string);
    CHECK_EXPRESSION(is_equal(test_string,
                              "Hallo du _____Hallo du _____") == BTRU);

    string_t test_string3 = allocate_strcpy("Hello");
    string_t test_string4 = allocate_strcpy("Hello ");
    CHECK_EXPRESSION(is_equal(r_trim(test_string3), "Hello") == BTRU);
    CHECK_EXPRESSION(is_equal(r_trim(test_string4), "Hello") == BTRU);

    string_t string_vector[] = {
        test_string, test_string2, test_string3, test_string4};
    CHECK_EXPRESSION(strlen_n(string_vector, 4) == 28);

    string_t test_string5 = allocate_strcpy("Hello");
    string_t test_string6 = allocate_strcpy("Hello  ");
    string_t test_string7 = allocate_strcpy("  Hello");
    CHECK_EXPRESSION(is_equal(trim(test_string5), "Hello") == BTRU);
    CHECK_EXPRESSION(is_equal(trim(test_string6), "Hello") == BTRU);
    CHECK_EXPRESSION(is_equal(trim(test_string7), "Hello") == BTRU);

    DEALLOCATE(test_string);
    DEALLOCATE(test_string2);
    DEALLOCATE(test_string3);
    DEALLOCATE(test_string4);
    DEALLOCATE(test_string5);
    DEALLOCATE(test_string6);
    DEALLOCATE(test_string7);

    return 0;
}