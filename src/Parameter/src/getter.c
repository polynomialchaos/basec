/*******************************************************************************
 * @file getter.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include "parameter_private.h"

/*******************************************************************************
 * @brief Get a parameter and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @param type
 * @param value
 ******************************************************************************/
void get_parameter_pass(cstring_t _file, int _line, cstring_t _function,
                        cstring_t path, parameter_type_t type, void *value)
{
    JSON_t *tmp = get_parameter_path_pass(_file, _line, _function, path, 1);
    get_json_value_pass(_file, _line, _function, tmp, as_json_type[type], value);
}

/*******************************************************************************
 * @brief Get a vector parameter count and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @return int
 ******************************************************************************/
int get_parameter_count_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path)
{
    JSON_t *tmp = get_parameter_path_pass(_file, _line, _function, path, 1);
    return count_json_childs(tmp);
}

/*******************************************************************************
 * @brief Get a vector parameter and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @param value
 * @param type
 * @param n
 ******************************************************************************/
void get_parameter_n_pass(cstring_t _file, int _line, cstring_t _function,
                          cstring_t path, void **value,
                          parameter_type_t type, size_t *n)
{
    JSON_t *tmp = get_parameter_path_pass(_file, _line, _function, path, 1);
    get_json_value_n_pass(_file, _line, _function, tmp, as_json_type[type], value, n);
}

/*******************************************************************************
 * @brief Check if parameter exists and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @return int
 ******************************************************************************/
bool_t parameter_exists_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path)
{
    return (get_parameter_path_pass(_file, _line, _function, path, 0) != NULL);
}

JSON_t *get_parameter_path_pass(cstring_t _file, int _line, cstring_t _function,
                                cstring_t path, int is_required)
{
    check_expression_pass(_file, _line, _function, user_defaults != NULL);
    string_t path_value = ALLOCATE(
        sizeof(char) * (strlen(path) + 1 + strlen(PVLK) + 1));
    strcpy(path_value, path);
    strcat(strcat(path_value, "/"), PVLK);

    JSON_t *result = NULL;

    if (user_inputs != NULL)
        result = get_json_object_by_path_pass(_file, _line, _function,
                                              user_inputs, path_value);

    if ((user_inputs != NULL) && (result == NULL))
        result = get_json_object_by_path_pass(_file, _line, _function,
                                              user_inputs, path);

    if (result == NULL)
        result = get_json_object_by_path_pass(_file, _line, _function,
                                              user_defaults, path_value);

    if (result == NULL)
        result = get_json_object_by_path_pass(_file, _line, _function,
                                              user_defaults, path);

    if (is_required)
        check_expression_pass(_file, _line, _function, result != NULL);

    DEALLOCATE(path_value);
    return result;
}