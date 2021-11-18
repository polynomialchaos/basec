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
 * @brief Append no chars to an other string
 * @param string
 * @param append
 * @param n
 * @return string_t
 ******************************************************************************/
string_t append_string(string_t string, string_t append, size_t n)
{
    size_t length = (string == NULL) ? 0 : strlen(string);
    string = REALLOCATE(string, sizeof(char) * (length + n + 1));

    strncpy(&string[length], append, n);
    string[length + n] = BNCH;

    return string;
}

/*******************************************************************************
 * @brief Fill and read buffer
 * @param buffer
 ******************************************************************************/
void fill_read_buffer(buffer_t *buffer)
{
    if (buffer->is_eof == EOF)
        return;

    while (buffer->cursor + buffer->length < JBFL)
    {
        // file read section
        if (buffer->is_file)
        {
            buffer->is_eof = fgetc(buffer->file);
        }
        else
        {
            buffer->is_eof = *buffer->string;
            if ((char)buffer->is_eof == BNCH)
                buffer->is_eof = EOF;
            else
                buffer->string++;
        }

        if (buffer->is_eof == EOF)
            break;

        // char parse section
        char tmp = (char)buffer->is_eof;

        if ((!buffer->is_control) && (tmp == '"'))
            buffer->skip = !buffer->skip ? BTRU : BFLS;

        if ((buffer->skip && (tmp == ' ')) ||
            (tmp == '\n') || (tmp == '\r') || (tmp == '\t'))
            continue;

        buffer->is_control = (tmp == '\\');
        buffer->buffer[buffer->cursor + buffer->length] = tmp;
        buffer->length++;
    }
}

/*******************************************************************************
 * @brief Increment and read buffer
 * @param buffer
 ******************************************************************************/
void increment_read_buffer(buffer_t *buffer)
{
    buffer->cursor++;
    if (buffer->cursor > JBFL - 1)
        buffer->cursor = 0;

    if (buffer->length > 0)
        buffer->length--;

    if (buffer->length == 0)
        fill_read_buffer(buffer);
}

/*******************************************************************************
 * @brief Parse a JSON array
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_array(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer)
{
    if (buffer->buffer[buffer->cursor] == ']')
        return;

    JSON_t *child = create_json_child_pass(_file, _line, _function, this);

    parse_json_value(_file, _line, _function, child, buffer);
}

/*******************************************************************************
 * @brief Parse a JSON object
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_object(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, buffer_t *buffer)
{
    if (buffer->buffer[buffer->cursor] == '}')
        return;

    check_expression_pass(_file, _line, _function, buffer->buffer[buffer->cursor] == '"');
    increment_read_buffer(buffer);

    size_t pos = 0;
    char tmp_string[JBFL];

    string_t tmp = NULL;
    while (buffer->length > 0)
    {
        if (buffer->buffer[buffer->cursor] == '"')
            break;

        if (pos >= JBFL - 1)
        {
            tmp = append_string(tmp, tmp_string, pos);
            pos = 0;
        }

        tmp_string[pos] = buffer->buffer[buffer->cursor];
        pos++;

        increment_read_buffer(buffer);
    }

    tmp = append_string(tmp, tmp_string, pos);

    check_expression_pass(_file, _line, _function, buffer->buffer[buffer->cursor] == '"');
    increment_read_buffer(buffer);

    check_expression_pass(_file, _line, _function, buffer->buffer[buffer->cursor] == ':');
    increment_read_buffer(buffer);

    JSON_t *child = create_json_child_pass(_file, _line, _function, this);
    set_json_key_pass(_file, _line, _function, child, tmp);

    DEALLOCATE(tmp);

    parse_json_value(_file, _line, _function, child, buffer);
}

/*******************************************************************************
 * @brief Parse a JSON value
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer)
{
    fill_read_buffer(buffer);
    if (buffer->length == 0)
        return;

    switch (buffer->buffer[buffer->cursor])
    {
    case '{':
        increment_read_buffer(buffer);
        set_json_type_pass(_file, _line, _function, this, JSONObject);
        parse_json_object(_file, _line, _function, this, buffer);
        while (buffer->buffer[buffer->cursor] == ',')
        {
            increment_read_buffer(buffer);
            parse_json_object(_file, _line, _function, this, buffer);
        }
        check_expression_pass(_file, _line, _function, buffer->buffer[buffer->cursor] == '}');
        increment_read_buffer(buffer);
        break;
    case '[':
        increment_read_buffer(buffer);
        set_json_type_pass(_file, _line, _function, this, JSONArray);
        parse_json_array(_file, _line, _function, this, buffer);
        while (buffer->buffer[buffer->cursor] == ',')
        {
            increment_read_buffer(buffer);
            parse_json_array(_file, _line, _function, this, buffer);
        }
        check_expression_pass(_file, _line, _function, buffer->buffer[buffer->cursor] == ']');
        increment_read_buffer(buffer);
        break;
    case 'n':
        parse_json_value_null(_file, _line, _function, this, buffer);
        break;
    case 't':
        parse_json_value_boolean(_file, _line, _function, this, buffer);
        break;
    case 'f':
        parse_json_value_boolean(_file, _line, _function, this, buffer);
        break;
    case '-':
        parse_json_value_number(_file, _line, _function, this, buffer);
        break;
    case '0' ... '9':
        parse_json_value_number(_file, _line, _function, this, buffer);
        break;
    case '"':
        increment_read_buffer(buffer);
        parse_json_value_string(_file, _line, _function, this, buffer);
        check_expression_pass(_file, _line, _function, buffer->buffer[buffer->cursor] == '"');
        increment_read_buffer(buffer);
        break;
    default:
        log_error_pass(_file, _line, _function,
                       "Unknown JSON parse type character (%c)!", buffer->buffer[buffer->cursor]);
        break;
    }
}

/*******************************************************************************
 * @brief Parse a JSON logical
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_boolean(cstring_t _file, int _line, cstring_t _function,
                              JSON_t *this, buffer_t *buffer)
{
    size_t pos = 0;
    char tmp_string[JBFL];

    while (buffer->length > 0)
    {
        if (buffer->buffer[buffer->cursor] == '"')
            break;
        if (buffer->buffer[buffer->cursor] == '}')
            break;
        if (buffer->buffer[buffer->cursor] == ']')
            break;
        if (buffer->buffer[buffer->cursor] == ',')
            break;

        if (pos >= JBFL - 1)
        {
            this->string = append_string(this->string, tmp_string, pos);
            pos = 0;
        }

        tmp_string[pos] = buffer->buffer[buffer->cursor];
        pos++;

        increment_read_buffer(buffer);
    }

    this->string = append_string(this->string, tmp_string, pos);

    check_expression_pass(_file, _line, _function,
                          is_equal(JTRU, this->string) || is_equal(JFLS, this->string));

    set_json_type_pass(_file, _line, _function, this, JSONBoolean);
    string_to(this->string, LogicalType, &this->boolean);
}

/*******************************************************************************
 * @brief Parse a JSON null object
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_null(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, buffer_t *buffer)
{
    size_t pos = 0;
    char tmp_string[JBFL];

    while (buffer->length > 0)
    {
        if (buffer->buffer[buffer->cursor] == '"')
            break;
        if (buffer->buffer[buffer->cursor] == '}')
            break;
        if (buffer->buffer[buffer->cursor] == ']')
            break;
        if (buffer->buffer[buffer->cursor] == ',')
            break;

        if (pos >= JBFL - 1)
        {
            this->string = append_string(this->string, tmp_string, pos);
            pos = 0;
        }

        tmp_string[pos] = buffer->buffer[buffer->cursor];
        pos++;

        increment_read_buffer(buffer);
    }

    this->string = append_string(this->string, tmp_string, pos);

    check_expression_pass(_file, _line, _function, is_equal(JNLL, this->string));
    set_json_type_pass(_file, _line, _function, this, JSONNull);
}

/*******************************************************************************
 * @brief Parse a JSON number
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_number(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer)
{
    size_t pos = 0;
    char tmp_string[JBFL];

    while (buffer->length > 0)
    {
        if (buffer->buffer[buffer->cursor] == '"')
            break;
        if (buffer->buffer[buffer->cursor] == '}')
            break;
        if (buffer->buffer[buffer->cursor] == ']')
            break;
        if (buffer->buffer[buffer->cursor] == ',')
            break;

        if (pos >= JBFL - 1)
        {
            this->string = append_string(this->string, tmp_string, pos);
            pos = 0;
        }

        tmp_string[pos] = buffer->buffer[buffer->cursor];
        pos++;

        increment_read_buffer(buffer);
    }

    this->string = append_string(this->string, tmp_string, pos);

    if (is_digit(this->string))
    {
        set_json_type_pass(_file, _line, _function, this, JSONDigit);
        string_to(this->string, DigitType, &this->digit);
    }
    else if (is_number(this->string))
    {
        set_json_type_pass(_file, _line, _function, this, JSONNumber);
        string_to(this->string, NumberType, &this->number);
    }
    else
    {
        log_error_pass(_file, _line, _function,
                       "Unsupported JSON type digit/number string (%s)!", this->string);
    }
}

/*******************************************************************************
 * @brief Parse a JSON string
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_string(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer)
{
    size_t pos = 0;
    char tmp_string[JBFL];

    bool_t is_control = BFLS;
    while (buffer->length > 0)
    {
        if ((!is_control) && (buffer->buffer[buffer->cursor] == '"'))
            break;

        is_control = (buffer->buffer[buffer->cursor] == '\\');

        if (pos >= JBFL - 1)
        {
            this->string = append_string(this->string, tmp_string, pos);
            pos = 0;
        }

        tmp_string[pos] = buffer->buffer[buffer->cursor];
        pos++;

        increment_read_buffer(buffer);
    }

    this->string = append_string(this->string, tmp_string, pos);

    set_json_type_pass(_file, _line, _function, this, JSONString);
}
