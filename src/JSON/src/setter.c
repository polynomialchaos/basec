/*******************************************************************************
 * @file setter.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <string.h>
#include "json_private.h"

/*******************************************************************************
 * @brief Set the JSON object key and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] keys
 ******************************************************************************/
void set_json_key_pass(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, cstring_t key)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, this != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, key != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, key[0] != BC_NLCH);

    this->key = allocate_strcpy(key);
}

/*******************************************************************************
 * @brief Se a JSON object by path and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *set_json_object_by_path_pass(cstring_t _file, int _line,
                                     cstring_t _function,
                                     JSON_t *this, cstring_t path)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, this != NULL);

    /** either path is NULL or empty, or base level is called */
    if (is_empty(path))
        return this;

    /** allocate level substring */
    size_t len = strcspn(path, "/");
    string_t level = BM_ALLOCATE(sizeof(char) * (len + 1));
    strncpy(level, path, len);
    level[len] = BC_NLCH;

    /** loop through childs an break on identical level/key */
    JSON_t *result = NULL;
    for (size_t i = 0; i < list_length(this->childs); ++i)
    {
        JSON_t *tmp = BM_LIST_GET_ITH(this->childs, i);
        if ((tmp->key != NULL) && is_equal(level, tmp->key))
        {
            result = tmp;
            break;
        }
    }

    /** child not found */
    if (result == NULL)
    {
        result = create_json_child_pass(_file, _line, _function, this);
        set_json_key_pass(_file, _line, _function, result, level);

        if (len_trim(path) > len + 1)
            set_json_type_pass(_file, _line, _function, result, JSONObject);
    }

    /** child found but path is not empty */
    if ((result != NULL) && (len_trim(path) > len + 1))
        result = set_json_object_by_path_pass(_file, _line, _function,
                                              result, &path[len + 1]);

    BM_DEALLOCATE(level);
    return result;
}

/*******************************************************************************
 * @brief Set the JSON object type and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 ******************************************************************************/
void set_json_type_pass(cstring_t _file, int _line, cstring_t _function,
                        JSON_t *this, json_type_t type)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, this != NULL);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function,
                             this->type == _JSONUndefined);
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function,
                             (type >= 0) && (type < _json_type_max));

    this->type = type;
}

/*******************************************************************************
 * @brief Set a JSON value at index i and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 * @param[in] value
 * @param[in] i
 ******************************************************************************/
void set_json_value_i_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t i)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, this != NULL);
    if (this->type == _JSONUndefined)
        set_json_type_pass(_file, _line, _function, this, type);
    else
        BM_CHECK_EXPRESSION_PASS(_file, _line, _function, this->type == type);

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
        BM_LOG_ERROR_PASS(_file, _line, _function, JERR, type);
        break;
    }
}

/*******************************************************************************
 * @brief Set a JSON value vector and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 * @param[in] value
 * @param[in] n
 ******************************************************************************/
void set_json_value_n_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t n)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, this != NULL);
    if (this->type == _JSONUndefined)
        set_json_type_pass(_file, _line, _function, this, JSONArray);
    else
        BM_CHECK_EXPRESSION_PASS(_file, _line, _function,
                                 this->type == JSONArray);

    for (size_t i = 0; i < n; ++i)
    {
        JSON_t *tmp = create_json_child_pass(_file, _line, _function, this);
        set_json_value_i_pass(_file, _line, _function, tmp, type, value, i);
    }
}