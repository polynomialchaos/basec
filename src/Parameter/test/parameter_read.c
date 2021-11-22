/*******************************************************************************
 * @file parameter_read.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/utils_module.h"
#include "basec/parameter_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    read_user_inputs("parameters.json");
    print_user_inputs();

    // logical type
    bool_t log_value = BTRU;
    bool_t log_values[] = {BTRU, BFLS, BTRU, BTRU};

    // digit type
    int dig_value = 1;
    int dig_values[] = {-1, 2, 30, 5};

    // number type
    double num_value = 1;
    double num_values[] = {-1, 2, 30, 5};

    // string type
    string_t str_value = "String";
    string_t str_values[] = {"String 1", "String 2", "String 3", "String 4"};

    // read logical type
    bool_t log_rvalue = BFLS;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/scalar/bool") == BTRU);
    GET_PARAMETER("section/bool/scalar/bool", LogicalType, &log_rvalue);
    CHECK_EXPRESSION(log_rvalue == log_value);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/scalar/bool_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/scalar/bool_desc/Description") == BTRU);
    GET_PARAMETER("section/bool/scalar/bool_desc", LogicalType, &log_rvalue);
    CHECK_EXPRESSION(log_rvalue == log_value);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/scalar/bool_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/bool/scalar/bool_desc_opt/Description with options") ==
        BTRU);
    GET_PARAMETER("section/bool/scalar/bool_desc_opt", LogicalType,
                  &log_rvalue);
    CHECK_EXPRESSION(log_rvalue == log_value);

    size_t n_log_rvalues = 0;
    bool_t *log_rvalues = NULL;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/vector/bool") == BTRU);
    CHECK_EXPRESSION(GET_PARAMETER_COUNT("section/bool/vector/bool") == 4);
    GET_PARAMETER_N("section/bool/vector/bool", LogicalType,
                    VOID_REF(log_rvalues), &n_log_rvalues);
    CHECK_EXPRESSION(n_log_rvalues == 4);
    CHECK_EXPRESSION(log_rvalues[0] == log_values[0]);
    CHECK_EXPRESSION(log_rvalues[1] == log_values[1]);
    CHECK_EXPRESSION(log_rvalues[2] == log_values[2]);
    CHECK_EXPRESSION(log_rvalues[3] == log_values[3]);
    DEALLOCATE(log_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/vector/bool_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/scalar/bool_desc/Description") == BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/bool/vector/bool_desc") == 4);
    GET_PARAMETER_N("section/bool/vector/bool_desc", LogicalType,
                    VOID_REF(log_rvalues), &n_log_rvalues);
    CHECK_EXPRESSION(n_log_rvalues == 4);
    CHECK_EXPRESSION(log_rvalues[0] == log_values[0]);
    CHECK_EXPRESSION(log_rvalues[1] == log_values[1]);
    CHECK_EXPRESSION(log_rvalues[2] == log_values[2]);
    CHECK_EXPRESSION(log_rvalues[3] == log_values[3]);
    DEALLOCATE(log_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/bool/vector/bool_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/bool/scalar/bool_desc_opt/Description with options") ==
        BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/bool/vector/bool_desc_opt") == 4);
    GET_PARAMETER_N("section/bool/vector/bool_desc_opt", LogicalType,
                    VOID_REF(log_rvalues), &n_log_rvalues);
    CHECK_EXPRESSION(n_log_rvalues == 4);
    CHECK_EXPRESSION(log_rvalues[0] == log_values[0]);
    CHECK_EXPRESSION(log_rvalues[1] == log_values[1]);
    CHECK_EXPRESSION(log_rvalues[2] == log_values[2]);
    CHECK_EXPRESSION(log_rvalues[3] == log_values[3]);
    DEALLOCATE(log_rvalues);

    // read digit type
    int dig_rvalue = 0;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/scalar/digit") == BTRU);
    GET_PARAMETER("section/digit/scalar/digit", DigitType, &dig_rvalue);
    CHECK_EXPRESSION(dig_rvalue == dig_value);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/scalar/digit_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/scalar/digit_desc/Description") == BTRU);
    GET_PARAMETER("section/digit/scalar/digit_desc", DigitType, &dig_rvalue);
    CHECK_EXPRESSION(dig_rvalue == dig_value);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/scalar/digit_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/digit/scalar/digit_desc_opt/Description with options") ==
        BTRU);
    GET_PARAMETER("section/digit/scalar/digit_desc_opt", DigitType,
                  &dig_rvalue);
    CHECK_EXPRESSION(dig_rvalue == dig_value);

    size_t n_dig_rvalues = 0;
    int *dig_rvalues = NULL;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/vector/digit") == BTRU);
    CHECK_EXPRESSION(GET_PARAMETER_COUNT("section/digit/vector/digit") == 4);
    GET_PARAMETER_N("section/digit/vector/digit", DigitType,
                    VOID_REF(dig_rvalues), &n_dig_rvalues);
    CHECK_EXPRESSION(n_dig_rvalues == 4);
    CHECK_EXPRESSION(dig_rvalues[0] == dig_values[0]);
    CHECK_EXPRESSION(dig_rvalues[1] == dig_values[1]);
    CHECK_EXPRESSION(dig_rvalues[2] == dig_values[2]);
    CHECK_EXPRESSION(dig_rvalues[3] == dig_values[3]);
    DEALLOCATE(dig_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/vector/digit_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/scalar/digit_desc/Description") == BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/digit/vector/digit_desc") == 4);
    GET_PARAMETER_N("section/digit/vector/digit_desc", DigitType,
                    VOID_REF(dig_rvalues), &n_dig_rvalues);
    CHECK_EXPRESSION(n_dig_rvalues == 4);
    CHECK_EXPRESSION(dig_rvalues[0] == dig_values[0]);
    CHECK_EXPRESSION(dig_rvalues[1] == dig_values[1]);
    CHECK_EXPRESSION(dig_rvalues[2] == dig_values[2]);
    CHECK_EXPRESSION(dig_rvalues[3] == dig_values[3]);
    DEALLOCATE(dig_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/digit/vector/digit_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/digit/scalar/digit_desc_opt/Description with options") ==
        BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/digit/vector/digit_desc_opt") == 4);
    GET_PARAMETER_N("section/digit/vector/digit_desc_opt", DigitType,
                    VOID_REF(dig_rvalues), &n_dig_rvalues);
    CHECK_EXPRESSION(n_dig_rvalues == 4);
    CHECK_EXPRESSION(dig_rvalues[0] == dig_values[0]);
    CHECK_EXPRESSION(dig_rvalues[1] == dig_values[1]);
    CHECK_EXPRESSION(dig_rvalues[2] == dig_values[2]);
    CHECK_EXPRESSION(dig_rvalues[3] == dig_values[3]);
    DEALLOCATE(dig_rvalues);

    // read number type
    double num_rvalue = 0;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/scalar/number") == BTRU);
    GET_PARAMETER("section/number/scalar/number", NumberType, &num_rvalue);
    CHECK_EXPRESSION(num_rvalue == num_value);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/scalar/number_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/scalar/number_desc/Description") == BTRU);
    GET_PARAMETER("section/number/scalar/number_desc", NumberType, &num_rvalue);
    CHECK_EXPRESSION(num_rvalue == num_value);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/scalar/number_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/number/scalar/number_desc_opt/Description with options") ==
        BTRU);
    GET_PARAMETER("section/number/scalar/number_desc_opt", NumberType,
                  &num_rvalue);
    CHECK_EXPRESSION(num_rvalue == num_value);

    size_t n_num_rvalues = 0;
    double *num_rvalues = NULL;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/vector/number") == BTRU);
    CHECK_EXPRESSION(GET_PARAMETER_COUNT("section/number/vector/number") == 4);
    GET_PARAMETER_N("section/number/vector/number", NumberType,
                    VOID_REF(num_rvalues), &n_num_rvalues);
    CHECK_EXPRESSION(n_num_rvalues == 4);
    CHECK_EXPRESSION(num_rvalues[0] == num_values[0]);
    CHECK_EXPRESSION(num_rvalues[1] == num_values[1]);
    CHECK_EXPRESSION(num_rvalues[2] == num_values[2]);
    CHECK_EXPRESSION(num_rvalues[3] == num_values[3]);
    DEALLOCATE(num_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/vector/number_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/scalar/number_desc/Description") == BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/number/vector/number_desc") == 4);
    GET_PARAMETER_N("section/number/vector/number_desc", NumberType,
                    VOID_REF(num_rvalues), &n_num_rvalues);
    CHECK_EXPRESSION(n_num_rvalues == 4);
    CHECK_EXPRESSION(num_rvalues[0] == num_values[0]);
    CHECK_EXPRESSION(num_rvalues[1] == num_values[1]);
    CHECK_EXPRESSION(num_rvalues[2] == num_values[2]);
    CHECK_EXPRESSION(num_rvalues[3] == num_values[3]);
    DEALLOCATE(num_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/number/vector/number_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/number/scalar/number_desc_opt/Description with options") ==
        BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/number/vector/number_desc_opt") == 4);
    GET_PARAMETER_N("section/number/vector/number_desc_opt", NumberType,
                    VOID_REF(num_rvalues), &n_num_rvalues);
    CHECK_EXPRESSION(n_num_rvalues == 4);
    CHECK_EXPRESSION(num_rvalues[0] == num_values[0]);
    CHECK_EXPRESSION(num_rvalues[1] == num_values[1]);
    CHECK_EXPRESSION(num_rvalues[2] == num_values[2]);
    CHECK_EXPRESSION(num_rvalues[3] == num_values[3]);
    DEALLOCATE(num_rvalues);

    // read string type
    string_t str_rvalue = NULL;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/scalar/string") == BTRU);
    GET_PARAMETER("section/string/scalar/string", StringType, &str_rvalue);
    CHECK_EXPRESSION(is_equal(str_rvalue, str_value));
    DEALLOCATE(str_rvalue);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/scalar/string_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/scalar/string_desc/Description") == BTRU);
    GET_PARAMETER("section/string/scalar/string_desc", StringType, &str_rvalue);
    CHECK_EXPRESSION(is_equal(str_rvalue, str_value));
    DEALLOCATE(str_rvalue);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/scalar/string_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/string/scalar/string_desc_opt/Description with options") ==
        BTRU);
    GET_PARAMETER("section/string/scalar/string_desc_opt", StringType,
                  &str_rvalue);
    CHECK_EXPRESSION(is_equal(str_rvalue, str_value));
    DEALLOCATE(str_rvalue);

    size_t n_str_rvalues = 0;
    string_t *str_rvalues = NULL;
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/vector/string") == BTRU);
    CHECK_EXPRESSION(GET_PARAMETER_COUNT("section/string/vector/string") == 4);
    GET_PARAMETER_N("section/string/vector/string", StringType,
                    VOID_REF(str_rvalues), &n_str_rvalues);
    CHECK_EXPRESSION(n_str_rvalues == 4);
    CHECK_EXPRESSION(is_equal(str_rvalues[0], str_values[0]));
    CHECK_EXPRESSION(is_equal(str_rvalues[1], str_values[1]));
    CHECK_EXPRESSION(is_equal(str_rvalues[2], str_values[2]));
    CHECK_EXPRESSION(is_equal(str_rvalues[3], str_values[3]));
    for(size_t i = 0; i < n_str_rvalues; ++i)
        DEALLOCATE(str_rvalues[i]);
    DEALLOCATE(str_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/vector/string_desc") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/scalar/string_desc/Description") == BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/string/vector/string_desc") == 4);
    GET_PARAMETER_N("section/string/vector/string_desc", StringType,
                    VOID_REF(str_rvalues), &n_str_rvalues);
    CHECK_EXPRESSION(n_str_rvalues == 4);
    CHECK_EXPRESSION(is_equal(str_rvalues[0], str_values[0]));
    CHECK_EXPRESSION(is_equal(str_rvalues[1], str_values[1]));
    CHECK_EXPRESSION(is_equal(str_rvalues[2], str_values[2]));
    CHECK_EXPRESSION(is_equal(str_rvalues[3], str_values[3]));
    for(size_t i = 0; i < n_str_rvalues; ++i)
        DEALLOCATE(str_rvalues[i]);
    DEALLOCATE(str_rvalues);

    CHECK_EXPRESSION(
        PARAMETER_EXISTS("section/string/vector/string_desc_opt") == BTRU);
    CHECK_EXPRESSION(
        PARAMETER_EXISTS(
            "section/string/scalar/string_desc_opt/Description with options") ==
        BTRU);
    CHECK_EXPRESSION(
        GET_PARAMETER_COUNT("section/string/vector/string_desc_opt") == 4);
    GET_PARAMETER_N("section/string/vector/string_desc_opt", StringType,
                    VOID_REF(str_rvalues), &n_str_rvalues);
    CHECK_EXPRESSION(n_str_rvalues == 4);
    CHECK_EXPRESSION(is_equal(str_rvalues[0], str_values[0]));
    CHECK_EXPRESSION(is_equal(str_rvalues[1], str_values[1]));
    CHECK_EXPRESSION(is_equal(str_rvalues[2], str_values[2]));
    CHECK_EXPRESSION(is_equal(str_rvalues[3], str_values[3]));
    for(size_t i = 0; i < n_str_rvalues; ++i)
        DEALLOCATE(str_rvalues[i]);
    DEALLOCATE(str_rvalues);

    free_parameters();

    return 0;
}