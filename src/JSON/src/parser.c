/*******************************************************************************
 * @file parser.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "json_private.h"

/*******************************************************************************
 * @brief Parse a JSON file and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *parse_json_file_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path)
{
    check_expression_pass(_file, _line, _function, file_exists(path));
    JSON_t *root = create_json_object();

    buffer_t buffer;
    buffer.cursor = 0;
    buffer.length = 0;
    buffer.skip = TRUE;
    buffer.is_control = FALSE;

    buffer.is_file = TRUE;
    buffer.file = open_file(path);
    buffer.is_eof = 0;

    parse_json_value(_file, _line, _function, root, &buffer);

    close_file(buffer.file);
    return root;
}

/*******************************************************************************
 * @brief Parse a JSON string and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param string
 * @return JSON_t*
 ******************************************************************************/
JSON_t *parse_json_string_pass(cstring_t _file, int _line, cstring_t _function,
                               string_t string)
{
    JSON_t *root = create_json_object();

    buffer_t buffer;
    buffer.cursor = 0;
    buffer.length = 0;
    buffer.skip = TRUE;
    buffer.is_control = FALSE;

    buffer.is_file = FALSE;
    buffer.string = string;
    buffer.is_eof = 0;

    parse_json_value(_file, _line, _function, root, &buffer);

    return root;
}