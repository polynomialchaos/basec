/*******************************************************************************
 * @file parameter_read.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "basec/utils_module.h"
#include "basec/parameter_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    read_user_inputs("parameters.json");
    print_user_inputs();

    /* logical type */
    bool_t log_value = BC_TRUE;
    bool_t log_values[] = {BC_TRUE, BC_FALSE, BC_TRUE, BC_TRUE};

    /* digit type */
    int dig_value = 1;
    int dig_values[] = {-1, 2, 30, 5};

    /* number type */
    double num_value = 1;
    double num_values[] = {-1, 2, 30, 5};

    /* string type */
    string_t str_value = "String";
    string_t str_values[] = {"String 1", "String 2", "String 3", "String 4"};

    /* read logical type */
    bool_t log_rvalue = BC_FALSE;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/bool/scalar/bool") == BC_TRUE);
    BM_GET_PARAMETER("section/bool/scalar/bool", LogicalParameter, &log_rvalue);
    BM_CHECK_EXPRESSION(log_rvalue == log_value);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/bool/scalar/bool_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/bool/scalar/bool_desc/Description") == BC_TRUE);
    BM_GET_PARAMETER(
        "section/bool/scalar/bool_desc", LogicalParameter, &log_rvalue);
    BM_CHECK_EXPRESSION(log_rvalue == log_value);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/bool/scalar/bool_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/bool/scalar/bool_desc_opt/Description with options") ==
        BC_TRUE);
    BM_GET_PARAMETER("section/bool/scalar/bool_desc_opt", LogicalParameter,
                     &log_rvalue);
    BM_CHECK_EXPRESSION(log_rvalue == log_value);

    size_t n_log_rvalues = 0;
    bool_t *log_rvalues = NULL;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/bool/vector/bool") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/bool/vector/bool") == 4);
    BM_GET_PARAMETER_N("section/bool/vector/bool", LogicalParameter,
                       BM_VOID_REF(log_rvalues), &n_log_rvalues);
    BM_CHECK_EXPRESSION(n_log_rvalues == 4);
    BM_CHECK_EXPRESSION(log_rvalues[0] == log_values[0]);
    BM_CHECK_EXPRESSION(log_rvalues[1] == log_values[1]);
    BM_CHECK_EXPRESSION(log_rvalues[2] == log_values[2]);
    BM_CHECK_EXPRESSION(log_rvalues[3] == log_values[3]);
    BM_DEALLOCATE(log_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/bool/vector/bool_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/bool/scalar/bool_desc/Description") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/bool/vector/bool_desc") == 4);
    BM_GET_PARAMETER_N("section/bool/vector/bool_desc", LogicalParameter,
                       BM_VOID_REF(log_rvalues), &n_log_rvalues);
    BM_CHECK_EXPRESSION(n_log_rvalues == 4);
    BM_CHECK_EXPRESSION(log_rvalues[0] == log_values[0]);
    BM_CHECK_EXPRESSION(log_rvalues[1] == log_values[1]);
    BM_CHECK_EXPRESSION(log_rvalues[2] == log_values[2]);
    BM_CHECK_EXPRESSION(log_rvalues[3] == log_values[3]);
    BM_DEALLOCATE(log_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/bool/vector/bool_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/bool/scalar/bool_desc_opt/Description with options") ==
        BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/bool/vector/bool_desc_opt") == 4);
    BM_GET_PARAMETER_N("section/bool/vector/bool_desc_opt", LogicalParameter,
                       BM_VOID_REF(log_rvalues), &n_log_rvalues);
    BM_CHECK_EXPRESSION(n_log_rvalues == 4);
    BM_CHECK_EXPRESSION(log_rvalues[0] == log_values[0]);
    BM_CHECK_EXPRESSION(log_rvalues[1] == log_values[1]);
    BM_CHECK_EXPRESSION(log_rvalues[2] == log_values[2]);
    BM_CHECK_EXPRESSION(log_rvalues[3] == log_values[3]);
    BM_DEALLOCATE(log_rvalues);

    /* read digit type */
    int dig_rvalue = 0;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/digit/scalar/digit") == BC_TRUE);
    BM_GET_PARAMETER("section/digit/scalar/digit", DigitParameter, &dig_rvalue);
    BM_CHECK_EXPRESSION(dig_rvalue == dig_value);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/digit/scalar/digit_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/digit/scalar/digit_desc/Description") == BC_TRUE);
    BM_GET_PARAMETER(
        "section/digit/scalar/digit_desc", DigitParameter, &dig_rvalue);
    BM_CHECK_EXPRESSION(dig_rvalue == dig_value);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/digit/scalar/digit_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/digit/scalar/digit_desc_opt/Description with options") ==
        BC_TRUE);
    BM_GET_PARAMETER("section/digit/scalar/digit_desc_opt", DigitParameter,
                     &dig_rvalue);
    BM_CHECK_EXPRESSION(dig_rvalue == dig_value);

    size_t n_dig_rvalues = 0;
    int *dig_rvalues = NULL;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/digit/vector/digit") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/digit/vector/digit") == 4);
    BM_GET_PARAMETER_N("section/digit/vector/digit", DigitParameter,
                       BM_VOID_REF(dig_rvalues), &n_dig_rvalues);
    BM_CHECK_EXPRESSION(n_dig_rvalues == 4);
    BM_CHECK_EXPRESSION(dig_rvalues[0] == dig_values[0]);
    BM_CHECK_EXPRESSION(dig_rvalues[1] == dig_values[1]);
    BM_CHECK_EXPRESSION(dig_rvalues[2] == dig_values[2]);
    BM_CHECK_EXPRESSION(dig_rvalues[3] == dig_values[3]);
    BM_DEALLOCATE(dig_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/digit/vector/digit_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/digit/scalar/digit_desc/Description") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/digit/vector/digit_desc") == 4);
    BM_GET_PARAMETER_N("section/digit/vector/digit_desc", DigitParameter,
                       BM_VOID_REF(dig_rvalues), &n_dig_rvalues);
    BM_CHECK_EXPRESSION(n_dig_rvalues == 4);
    BM_CHECK_EXPRESSION(dig_rvalues[0] == dig_values[0]);
    BM_CHECK_EXPRESSION(dig_rvalues[1] == dig_values[1]);
    BM_CHECK_EXPRESSION(dig_rvalues[2] == dig_values[2]);
    BM_CHECK_EXPRESSION(dig_rvalues[3] == dig_values[3]);
    BM_DEALLOCATE(dig_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/digit/vector/digit_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/digit/scalar/digit_desc_opt/Description with options") ==
        BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/digit/vector/digit_desc_opt") == 4);
    BM_GET_PARAMETER_N("section/digit/vector/digit_desc_opt", DigitParameter,
                       BM_VOID_REF(dig_rvalues), &n_dig_rvalues);
    BM_CHECK_EXPRESSION(n_dig_rvalues == 4);
    BM_CHECK_EXPRESSION(dig_rvalues[0] == dig_values[0]);
    BM_CHECK_EXPRESSION(dig_rvalues[1] == dig_values[1]);
    BM_CHECK_EXPRESSION(dig_rvalues[2] == dig_values[2]);
    BM_CHECK_EXPRESSION(dig_rvalues[3] == dig_values[3]);
    BM_DEALLOCATE(dig_rvalues);

    /* read number type */
    double num_rvalue = 0;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/number/scalar/number") == BC_TRUE);
    BM_GET_PARAMETER(
        "section/number/scalar/number", NumberParameter, &num_rvalue);
    BM_CHECK_EXPRESSION(num_rvalue == num_value);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/number/scalar/number_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/number/scalar/number_desc/Description") == BC_TRUE);
    BM_GET_PARAMETER(
        "section/number/scalar/number_desc", NumberParameter, &num_rvalue);
    BM_CHECK_EXPRESSION(num_rvalue == num_value);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/number/scalar/number_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/number/scalar/number_desc_opt/Description with options") ==
        BC_TRUE);
    BM_GET_PARAMETER("section/number/scalar/number_desc_opt", NumberParameter,
                     &num_rvalue);
    BM_CHECK_EXPRESSION(num_rvalue == num_value);

    size_t n_num_rvalues = 0;
    double *num_rvalues = NULL;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/number/vector/number") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/number/vector/number") == 4);
    BM_GET_PARAMETER_N("section/number/vector/number", NumberParameter,
                       BM_VOID_REF(num_rvalues), &n_num_rvalues);
    BM_CHECK_EXPRESSION(n_num_rvalues == 4);
    BM_CHECK_EXPRESSION(num_rvalues[0] == num_values[0]);
    BM_CHECK_EXPRESSION(num_rvalues[1] == num_values[1]);
    BM_CHECK_EXPRESSION(num_rvalues[2] == num_values[2]);
    BM_CHECK_EXPRESSION(num_rvalues[3] == num_values[3]);
    BM_DEALLOCATE(num_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/number/vector/number_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/number/scalar/number_desc/Description") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/number/vector/number_desc") == 4);
    BM_GET_PARAMETER_N("section/number/vector/number_desc", NumberParameter,
                       BM_VOID_REF(num_rvalues), &n_num_rvalues);
    BM_CHECK_EXPRESSION(n_num_rvalues == 4);
    BM_CHECK_EXPRESSION(num_rvalues[0] == num_values[0]);
    BM_CHECK_EXPRESSION(num_rvalues[1] == num_values[1]);
    BM_CHECK_EXPRESSION(num_rvalues[2] == num_values[2]);
    BM_CHECK_EXPRESSION(num_rvalues[3] == num_values[3]);
    BM_DEALLOCATE(num_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/number/vector/number_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/number/scalar/number_desc_opt/Description with options") ==
        BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/number/vector/number_desc_opt") == 4);
    BM_GET_PARAMETER_N("section/number/vector/number_desc_opt", NumberParameter,
                       BM_VOID_REF(num_rvalues), &n_num_rvalues);
    BM_CHECK_EXPRESSION(n_num_rvalues == 4);
    BM_CHECK_EXPRESSION(num_rvalues[0] == num_values[0]);
    BM_CHECK_EXPRESSION(num_rvalues[1] == num_values[1]);
    BM_CHECK_EXPRESSION(num_rvalues[2] == num_values[2]);
    BM_CHECK_EXPRESSION(num_rvalues[3] == num_values[3]);
    BM_DEALLOCATE(num_rvalues);

    /* read string type */
    string_t str_rvalue = NULL;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/string/scalar/string") == BC_TRUE);
    BM_GET_PARAMETER(
        "section/string/scalar/string", StringParameter, &str_rvalue);
    BM_CHECK_EXPRESSION(is_equal(str_rvalue, str_value));
    BM_DEALLOCATE(str_rvalue);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/string/scalar/string_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/string/scalar/string_desc/Description") == BC_TRUE);
    BM_GET_PARAMETER(
        "section/string/scalar/string_desc", StringParameter, &str_rvalue);
    BM_CHECK_EXPRESSION(is_equal(str_rvalue, str_value));
    BM_DEALLOCATE(str_rvalue);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/string/scalar/string_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/string/scalar/string_desc_opt/Description with options") ==
        BC_TRUE);
    BM_GET_PARAMETER("section/string/scalar/string_desc_opt", StringParameter,
                     &str_rvalue);
    BM_CHECK_EXPRESSION(is_equal(str_rvalue, str_value));
    BM_DEALLOCATE(str_rvalue);

    size_t n_str_rvalues = 0;
    string_t *str_rvalues = NULL;
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/string/vector/string") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/string/vector/string") == 4);
    BM_GET_PARAMETER_N("section/string/vector/string", StringParameter,
                       BM_VOID_REF(str_rvalues), &n_str_rvalues);
    BM_CHECK_EXPRESSION(n_str_rvalues == 4);
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[0], str_values[0]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[1], str_values[1]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[2], str_values[2]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[3], str_values[3]));
    for (size_t i = 0; i < n_str_rvalues; ++i)
        BM_DEALLOCATE(str_rvalues[i]);
    BM_DEALLOCATE(str_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS("section/string/vector/string_desc") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/string/scalar/string_desc/Description") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/string/vector/string_desc") == 4);
    BM_GET_PARAMETER_N("section/string/vector/string_desc", StringParameter,
                       BM_VOID_REF(str_rvalues), &n_str_rvalues);
    BM_CHECK_EXPRESSION(n_str_rvalues == 4);
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[0], str_values[0]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[1], str_values[1]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[2], str_values[2]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[3], str_values[3]));
    for (size_t i = 0; i < n_str_rvalues; ++i)
        BM_DEALLOCATE(str_rvalues[i]);
    BM_DEALLOCATE(str_rvalues);

    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/string/vector/string_desc_opt") == BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_PARAMETER_EXISTS(
            "section/string/scalar/string_desc_opt/Description with options") ==
        BC_TRUE);
    BM_CHECK_EXPRESSION(
        BM_GET_PARAMETER_COUNT("section/string/vector/string_desc_opt") == 4);
    BM_GET_PARAMETER_N("section/string/vector/string_desc_opt", StringParameter,
                       BM_VOID_REF(str_rvalues), &n_str_rvalues);
    BM_CHECK_EXPRESSION(n_str_rvalues == 4);
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[0], str_values[0]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[1], str_values[1]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[2], str_values[2]));
    BM_CHECK_EXPRESSION(is_equal(str_rvalues[3], str_values[3]));
    for (size_t i = 0; i < n_str_rvalues; ++i)
        BM_DEALLOCATE(str_rvalues[i]);
    BM_DEALLOCATE(str_rvalues);

    free_parameters();

    return 0;
}