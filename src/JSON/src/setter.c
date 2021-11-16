/*******************************************************************************
 * @file setter.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include "json_private.h"

/*******************************************************************************
 * @brief Set the JSON object key and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param key
 ******************************************************************************/
void set_json_key_pass(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, cstring_t key)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    check_expression_pass(_file, _line, _function, (key != NULL) && (key[0] != NULL_CHAR));

    this->key = allocate_strcpy(key);
}

/*******************************************************************************
 * @brief Se a JSON object by path and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *set_json_object_by_path_pass(cstring_t _file, int _line,
                                     cstring_t _function,
                                     JSON_t *this, cstring_t path)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    if ((path == NULL) || (path[0] == NULL_CHAR))
        return this;

    size_t pos = strcspn(path, "/");
    string_t node = ALLOCATE(sizeof(char) * (pos + 1));
    strncpy(node, path, pos);
    node[pos] = NULL_CHAR;

    JSON_t *result = NULL;
    for (size_t i = 0; i < list_length(this->childs); ++i)
    {
        JSON_t *tmp = list_get_ith(this->childs, i);
        if ((tmp->key != NULL) && is_equal(node, tmp->key))
            result = tmp;
    }

    if (result == NULL)
    {
        result = create_json_child_pass(_file, _line, _function, this);
        set_json_key_pass(_file, _line, _function, result, node);

        if (pos + 1 < len_trim(path))
            set_json_type_pass(_file, _line, _function, result, JSONObject);
    }

    if ((result != NULL) && (pos + 1 < len_trim(path)))
        result = set_json_object_by_path_pass(_file, _line, _function,
                                              result, &path[pos + 1]);

    DEALLOCATE(node);
    return result;
}

/*******************************************************************************
 * @brief Set the JSON object type and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param type
 ******************************************************************************/
void set_json_type_pass(cstring_t _file, int _line, cstring_t _function,
                        JSON_t *this, json_type_t type)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    check_expression_pass(_file, _line, _function, (this->type == _JSONUndefined));
    check_expression_pass(_file, _line, _function, ((type >= 0) && (type < _json_type_max)));

    this->type = type;
}

/*******************************************************************************
 * @brief Set a JSON value at index i and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param type
 * @param value
 * @param i
 ******************************************************************************/
void set_json_value_i_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t i)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    if (this->type == _JSONUndefined)
        set_json_type_pass(_file, _line, _function, this, type);
    check_expression_pass(_file, _line, _function, (this->type == type));

    switch (type)
    {
    case JSONBoolean:
        this->type = JSONBoolean;
        this->boolean = ((bool_t *)value)[i];
        break;
    case JSONDigit:
        this->type = JSONDigit;
        this->digit = ((int *)value)[i];
        break;
    case JSONNumber:
        this->type = JSONNumber;
        this->number = ((double *)value)[i];
        break;
    case JSONString:
        this->type = JSONString;
        if (((string_t *)value)[i] != NULL)
        {
            this->string = allocate_strcpy(((string_t *)value)[i]);
        }
        break;
    default:
        log_error_pass(_file, _line, _function, JSON_ERROR, type);
        break;
    }
}

/*******************************************************************************
 * @brief Set a JSON value vector and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param type
 * @param value
 * @param n
 ******************************************************************************/
void set_json_value_n_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t n)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    if (this->type == _JSONUndefined)
        set_json_type_pass(_file, _line, _function, this, JSONArray);
    check_expression_pass(_file, _line, _function, (this->type == JSONArray));

    for (size_t i = 0; i < n; ++i)
    {
        JSON_t *tmp = create_json_child_pass(_file, _line, _function, this);
        set_json_value_i_pass(_file, _line, _function, tmp, type, value, i);
    }
}