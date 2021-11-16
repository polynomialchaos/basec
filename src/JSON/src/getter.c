/*******************************************************************************
 * @file getter.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include "json_private.h"

/** type size of JSON type */
const size_t json_type_size[_json_type_max] = {
    0, 0, 0,
    sizeof(int), sizeof(int), sizeof(double), sizeof(string_t)};

/*******************************************************************************
 * @brief Get a JSON object by path and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *get_json_object_by_path_pass(cstring_t _file, int _line,
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

    if ((result != NULL) && (pos + 1 < len_trim(path)))
        result = get_json_object_by_path_pass(_file, _line, _function,
                                              result, &path[pos + 1]);

    DEALLOCATE(node);
    return result;
}

/*******************************************************************************
 * @brief Get a JSON value at index i and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param type
 * @param value
 * @param i
 ******************************************************************************/
void get_json_value_i_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t i)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    check_expression_pass(_file, _line, _function, (this->type == type));

    switch (type)
    {
    case JSONBoolean:
        ((bool_t *)value)[i] = this->boolean;
        break;
    case JSONDigit:
        ((int *)value)[i] = this->digit;
        break;
    case JSONNumber:
        ((double *)value)[i] = this->number;
        break;
    case JSONString:
        if ((string_t)this->string != NULL)
        {
            ((string_t *)value)[i] = allocate_strcpy(this->string);
        }
        break;
    default:
        log_error_pass(_file, _line, _function, JSON_ERROR, type);
        break;
    }
}

/*******************************************************************************
 * @brief Get a JSON value vector and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param type
 * @param value
 * @param n
 ******************************************************************************/
void get_json_value_n_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void **value, size_t *n)
{
    check_expression_pass(_file, _line, _function, (this != NULL));
    check_expression_pass(_file, _line, _function, (this->type == JSONArray));

    (*n) = count_json_childs(this);
    (*value) = ALLOCATE(json_type_size[type] * (*n));

    for (size_t i = 0; i < (*n); ++i)
    {
        JSON_t *tmp = list_get_ith(this->childs, i);
        get_json_value_i_pass(_file, _line, _function, tmp, type, *value, i);
    }
}