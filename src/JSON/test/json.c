/*******************************************************************************
 * @file json.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"
#include "basec/json_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    bool_t data_bool[] = {BTRU, BFLS, BTRU, BTRU};
    int data_digit[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double data_number[] = {1.0, 2.0, 3.0, 4.0};
    char *data_string[] = {"Hello", "World"};

    JSON_t *root = create_json_object();
    SET_JSON_TYPE(root, JSONObject);

    JSON_t *child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONBoolean);
    SET_JSON_KEY(child, "bool_t value");
    SET_JSON_VALUE(child, JSONBoolean, &data_bool[0]);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONDigit);
    SET_JSON_KEY(child, "digit value");
    SET_JSON_VALUE(child, JSONDigit, &data_digit[0]);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONNumber);
    SET_JSON_KEY(child, "number value");
    SET_JSON_VALUE(child, JSONNumber, &data_number[0]);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONString);
    SET_JSON_KEY(child, "string value");
    SET_JSON_VALUE(child, JSONString, &data_string[0]);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONArray);
    SET_JSON_KEY(child, "bool_t vector");
    SET_JSON_VALUE_N(child, JSONBoolean, &data_bool[0], 4);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONArray);
    SET_JSON_KEY(child, "digit vector");
    SET_JSON_VALUE_N(child, JSONDigit, &data_digit[0], 10);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONArray);
    SET_JSON_KEY(child, "number vector");
    SET_JSON_VALUE_N(child, JSONNumber, &data_number[0], 4);

    child = CREATE_JSON_CHILD(root);
    SET_JSON_TYPE(child, JSONArray);
    SET_JSON_KEY(child, "string vector");
    SET_JSON_VALUE_N(child, JSONString, &data_string[0], 2);

    FILE *file = fopen("test.json", "w");
    PRINT_JSON_OBJECT_SHORT(root, file);
    fclose(file);

    free_json_object(root);
    DEALLOCATE(root);

    return 0;
}