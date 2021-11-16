/*******************************************************************************
 * @file setter.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "parameter_private.h"

/*******************************************************************************
 * @brief Set a parameter and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @param type
 * @param value
 * @param description
 * @param options
 * @param n_options
 ******************************************************************************/
void set_parameter_pass(cstring_t _file, int _line, cstring_t _function,
                        cstring_t path, parameter_type_t type,
                        void *value, cstring_t description,
                        void *options, size_t n_options)
{
    check_expression_pass(_file, _line, _function,
                          ((path != NULL) && (path[0] != NULL_CHAR)));

    if (user_defaults == NULL)
    {
        user_defaults = create_json_object();
        set_json_type_pass(_file, _line, _function, user_defaults, JSONObject);
    }

    JSON_t *tmp = set_json_object_by_path_pass(_file, _line, _function,
                                               user_defaults, path);

    if (description != NULL)
    {
        set_json_type_pass(_file, _line, _function, tmp, JSONObject);

        JSON_t *tmp_v = create_json_child_pass(_file, _line, _function, tmp);
        set_json_key_pass(_file, _line, _function, tmp_v, PARAMETER_VALUE_KEY);
        set_json_type_pass(_file, _line, _function, tmp_v, as_json_type[type]);
        set_json_value_pass(_file, _line, _function, tmp_v, as_json_type[type], value);

        JSON_t *tmp_d = create_json_child_pass(_file, _line, _function, tmp);
        set_json_key_pass(_file, _line, _function, tmp_d, description);
        if (options != NULL)
        {
            set_json_type_pass(_file, _line, _function, tmp_d, JSONArray);
            set_json_value_n_pass(_file, _line, _function, tmp_d, as_json_type[type],
                                  options, n_options);
        }
    }
    else
    {
        set_json_type_pass(_file, _line, _function, tmp, as_json_type[type]);
        set_json_value_pass(_file, _line, _function, tmp, as_json_type[type], value);
    }
}

/*******************************************************************************
 * @brief Set a vector parameter and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @param type
 * @param value
 * @param n
 * @param description
 * @param options
 * @param n_options
 ******************************************************************************/
void set_parameter_n_pass(cstring_t _file, int _line, cstring_t _function,
                          cstring_t path, parameter_type_t type,
                          void **value, size_t n, cstring_t description,
                          void *options, size_t n_options)
{
    check_expression_pass(_file, _line, _function,
                          ((path != NULL) && (path[0] != NULL_CHAR)));

    if (user_defaults == NULL)
    {
        user_defaults = create_json_object();
        set_json_type_pass(_file, _line, _function, user_defaults, JSONObject);
    }

    JSON_t *tmp = set_json_object_by_path_pass(_file, _line, _function,
                                               user_defaults, path);

    if (description != NULL)
    {
        set_json_type_pass(_file, _line, _function, tmp, JSONObject);

        JSON_t *tmp_v = create_json_child_pass(_file, _line, _function, tmp);
        set_json_key_pass(_file, _line, _function, tmp_v, PARAMETER_VALUE_KEY);
        set_json_type_pass(_file, _line, _function, tmp_v, as_json_type[type]);
        set_json_value_n_pass(_file, _line, _function, tmp_v, as_json_type[type],
                              value, n);

        JSON_t *tmp_d = create_json_child_pass(_file, _line, _function, tmp);
        set_json_key_pass(_file, _line, _function, tmp_d, description);
        if (options != NULL)
        {
            set_json_type_pass(_file, _line, _function, tmp_d, JSONArray);
            set_json_value_n_pass(_file, _line, _function, tmp_d, as_json_type[type],
                                  options, n_options);
        }
    }
    else
    {
        set_json_type_pass(_file, _line, _function, tmp, as_json_type[type]);
        set_json_value_n_pass(_file, _line, _function, tmp, as_json_type[type],
                              value, n);
    }
}