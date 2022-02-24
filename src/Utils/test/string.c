/*******************************************************************************
 * @file string.c
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
    string_t test_string = allocate_strcpy("Hallo du .....");
    BM_CHECK_EXPRESSION(test_string != NULL);
    BM_PRINT("%s\n", test_string);

    string_t test_string2 = allocate_strcat("Hallo", " du .....");
    BM_CHECK_EXPRESSION(test_string2 != NULL);
    BM_PRINT("%s\n", test_string2);

    BM_CHECK_EXPRESSION(count_chars(test_string2, '.') == 5);

    BM_CHECK_EXPRESSION(is_digit(test_string2) == BC_FALSE);
    BM_CHECK_EXPRESSION(is_digit("1.0") == BC_FALSE);
    BM_CHECK_EXPRESSION(is_digit("1") == BC_TRUE);

    BM_CHECK_EXPRESSION(is_equal(NULL, NULL) == BC_TRUE);
    BM_CHECK_EXPRESSION(is_equal(test_string, NULL) == BC_FALSE);
    BM_CHECK_EXPRESSION(is_equal(NULL, test_string) == BC_FALSE);
    BM_CHECK_EXPRESSION(is_equal(test_string, test_string2) == BC_TRUE);
    BM_CHECK_EXPRESSION(is_equal(test_string, "") == BC_FALSE);

    BM_CHECK_EXPRESSION(is_empty("") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_empty(NULL) == BC_TRUE);
    BM_CHECK_EXPRESSION(is_empty(test_string) == BC_FALSE);

    BM_CHECK_EXPRESSION(is_number(test_string2) == BC_FALSE);
    BM_CHECK_EXPRESSION(is_number("1.0") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_number("1.0e-16") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_number("1") == BC_FALSE);

    BM_CHECK_EXPRESSION(len_trim(NULL) == 0);
    BM_CHECK_EXPRESSION(len_trim("") == 0);
    BM_CHECK_EXPRESSION(len_trim(" Hello ") == 5);

    BM_CHECK_EXPRESSION(is_equal(l_trim("Hello"), "Hello") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_equal(l_trim("  Hello"), "Hello") == BC_TRUE);

    test_string = reallocate_strcat(test_string, test_string2);
    BM_CHECK_EXPRESSION(test_string != NULL);
    BM_PRINT("%s\n", test_string);

    replace(test_string, '.', '_');
    BM_PRINT("%s\n", test_string);
    BM_CHECK_EXPRESSION(is_equal(test_string,
                                 "Hallo du _____Hallo du _____") == BC_TRUE);

    string_t test_string3 = allocate_strcpy("Hello");
    string_t test_string4 = allocate_strcpy("Hello ");
    BM_CHECK_EXPRESSION(is_equal(r_trim(test_string3), "Hello") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_equal(r_trim(test_string4), "Hello") == BC_TRUE);

    string_t string_vector[] = {
        test_string, test_string2, test_string3, test_string4};
    BM_CHECK_EXPRESSION(strlen_n(string_vector, 4) == 28);

    string_t test_string5 = allocate_strcpy("Hello");
    string_t test_string6 = allocate_strcpy("Hello  ");
    string_t test_string7 = allocate_strcpy("  Hello");
    BM_CHECK_EXPRESSION(is_equal(trim(test_string5), "Hello") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_equal(trim(test_string6), "Hello") == BC_TRUE);
    BM_CHECK_EXPRESSION(is_equal(trim(test_string7), "Hello") == BC_TRUE);

    BM_DEALLOCATE(test_string);
    BM_DEALLOCATE(test_string2);
    BM_DEALLOCATE(test_string3);
    BM_DEALLOCATE(test_string4);
    BM_DEALLOCATE(test_string5);
    BM_DEALLOCATE(test_string6);
    BM_DEALLOCATE(test_string7);

    return 0;
}