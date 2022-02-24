/*******************************************************************************
 * @file parser.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "json_private.h"

/*******************************************************************************
 * @brief Parse a JSON file and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *parse_json_file_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path)
{
    BM_CHECK_EXPRESSION_PASS(_file, _line, _function, file_exists(path));
    JSON_t *root = create_json_object();

    buffer_t buffer;
    buffer.cursor = 0;
    buffer.length = 0;
    buffer.skip = BC_TRUE;
    buffer.is_control = BC_FALSE;

    buffer.is_file = BC_TRUE;
    buffer.file = open_file(path);
    buffer.is_eof = 0;

    parse_json_value(_file, _line, _function, root, &buffer);

    close_file(buffer.file);
    return root;
}

/*******************************************************************************
 * @brief Parse a JSON string and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] string
 * @return JSON_t*
 ******************************************************************************/
JSON_t *parse_json_string_pass(cstring_t _file, int _line, cstring_t _function,
                               string_t string)
{
    JSON_t *root = create_json_object();

    buffer_t buffer;
    buffer.cursor = 0;
    buffer.length = 0;
    buffer.skip = BC_TRUE;
    buffer.is_control = BC_FALSE;

    buffer.is_file = BC_FALSE;
    buffer.string = string;
    buffer.is_eof = 0;

    parse_json_value(_file, _line, _function, root, &buffer);

    return root;
}