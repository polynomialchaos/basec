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
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *get_json_object_by_path_pass(cstring_t _file, int _line,
                                     cstring_t _function,
                                     JSON_t *this, cstring_t path)
{
    check_expression_pass(_file, _line, _function, this != NULL);

    /** either path is NULL or empty, or base level is called */
    if (is_empty(path))
        return this;

    /** allocate level substring */
    size_t len = strcspn(path, "/");
    string_t level = ALLOCATE(sizeof(char) * (len + 1));
    strncpy(level, path, len);
    level[len] = BNCH;

    /** loop through childs an break on identical level/key */
    JSON_t *result = NULL;
    for (size_t i = 0; i < list_length(this->childs); ++i)
    {
        JSON_t *tmp = list_get_ith(this->childs, i);
        if ((tmp->key != NULL) && is_equal(level, tmp->key))
        {
            result = tmp;
            break;
        }
    }

    /** child found but path is not empty */
    if ((result != NULL) && (len_trim(path) > len + 1))
        result = get_json_object_by_path_pass(_file, _line, _function,
                                              result, &path[len + 1]);

    DEALLOCATE(level);
    return result;
}

/*******************************************************************************
 * @brief Get a JSON value at index i and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 * @param[in] i
 * @param[out] value
 ******************************************************************************/
void get_json_value_i_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           size_t i, void *value)
{
    check_expression_pass(_file, _line, _function, this != NULL);
    check_expression_pass(_file, _line, _function, this->type == type);

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
        log_error_pass(_file, _line, _function, JERR, type);
        break;
    }
}

/*******************************************************************************
 * @brief Get a JSON value vector and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 * @param[out] value
 * @param[out] n
 ******************************************************************************/
void get_json_value_n_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void **value, size_t *n)
{
    check_expression_pass(_file, _line, _function, this != NULL);
    check_expression_pass(_file, _line, _function, this->type == JSONArray);

    (*n) = count_json_childs(this);
    (*value) = ALLOCATE(json_type_size[type] * (*n));

    for (size_t i = 0; i < (*n); ++i)
    {
        JSON_t *tmp = list_get_ith(this->childs, i);
        get_json_value_i_pass(_file, _line, _function, tmp, type, i, *value);
    }
}
