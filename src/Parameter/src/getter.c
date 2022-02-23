/*******************************************************************************
 * @file getter.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <string.h>
#include "parameter_private.h"

/*******************************************************************************
 * @brief Get a parameter and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] type
 * @param[out] value
 ******************************************************************************/
void get_parameter_pass(cstring_t _file, int _line, cstring_t _function,
                        cstring_t path, parameter_type_t type, void *value)
{
    JSON_t *tmp = get_parameter_path_pass(_file, _line, _function, path, 1);
    GET_JSON_VALUE_PASS(_file, _line, _function, tmp, as_json_type[type], value);
}

/*******************************************************************************
 * @brief Get a vector parameter count and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
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
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] type
 * @param[out] value
 * @param[out] n
 ******************************************************************************/
void get_parameter_n_pass(cstring_t _file, int _line, cstring_t _function,
                          cstring_t path, parameter_type_t type,
                          void **value, size_t *n)
{
    JSON_t *tmp = get_parameter_path_pass(_file, _line, _function, path, 1);
    get_json_value_n_pass(_file, _line, _function, tmp, as_json_type[type], value, n);
}

/*******************************************************************************
 * @brief Check if parameter exists and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @return int
 ******************************************************************************/
bool_t parameter_exists_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path)
{
    return (get_parameter_path_pass(_file, _line, _function, path, 0) != NULL);
}

/*******************************************************************************
 * @brief Get the parameter object by path
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] is_required
 * @return JSON_t*
 ******************************************************************************/
JSON_t *get_parameter_path_pass(cstring_t _file, int _line, cstring_t _function,
                                cstring_t path, int is_required)
{
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
        CHECK_EXPRESSION_PASS(_file, _line, _function, result != NULL);

    DEALLOCATE(path_value);
    return result;
}