/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"
#include "basec/json_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    bool_t data_bool[] = {TRUE, FALSE, TRUE, TRUE};
    int data_digit[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double data_number[] = {1.0, 2.0, 3.0, 4.0};
    char *data_string[] = {"Hello", "World"};

    JSON_t *root = create_json_object();
    set_json_type(root, JSONObject);

    JSON_t *child = create_json_child(root);
    set_json_type(child, JSONBoolean);
    set_json_key(child, "bool_t value");
    set_json_value(child, JSONBoolean, &data_bool[0]);

    child = create_json_child(root);
    set_json_type(child, JSONDigit);
    set_json_key(child, "digit value");
    set_json_value(child, JSONDigit, &data_digit[0]);

    child = create_json_child(root);
    set_json_type(child, JSONNumber);
    set_json_key(child, "number value");
    set_json_value(child, JSONNumber, &data_number[0]);

    child = create_json_child(root);
    set_json_type(child, JSONString);
    set_json_key(child, "string value");
    set_json_value(child, JSONString, &data_string[0]);

    child = create_json_child(root);
    set_json_type(child, JSONArray);
    set_json_key(child, "bool_t vector");
    set_json_value_n(child, JSONBoolean, &data_bool[0], 4);

    child = create_json_child(root);
    set_json_type(child, JSONArray);
    set_json_key(child, "digit vector");
    set_json_value_n(child, JSONDigit, &data_digit[0], 10);

    child = create_json_child(root);
    set_json_type(child, JSONArray);
    set_json_key(child, "number vector");
    set_json_value_n(child, JSONNumber, &data_number[0], 4);

    child = create_json_child(root);
    set_json_type(child, JSONArray);
    set_json_key(child, "string vector");
    set_json_value_n(child, JSONString, &data_string[0], 2);

    FILE *file = fopen("test.json", "w");
    print_json_object_short(root, file);
    fclose(file);

    free_json_object(root);
    DEALLOCATE(root);

    root = parse_json_file("test.json");
    print_json_object(root, get_stdout());

    JSON_t *tmp = get_json_object_by_path(root, "number vector");
    double *data;
    size_t n;
    get_json_value_n(tmp, JSONNumber, VOID_REF(data), &n);
    printf_r("%ld\n", n);
    DEALLOCATE(data);

    free_json_object(root);
    DEALLOCATE(root);

    root = parse_json_string("{\"a\":[12,13,14,15]}");
    print_json_object_indent(root, get_stdout(), -1);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}