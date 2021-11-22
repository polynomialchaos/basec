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

#define JWSP ' '  /** Whitespace */
#define JNWL '\n' /** Newline */
#define JTBS '\t' /** Tabstop */
#define JRET '\r' /** Return */
#define JCTR '\\' /** Control */

#define JLBC '{' /** Left brace */
#define JRBC '}' /** Right brace */
#define JLBK '[' /** Left bracket */
#define JRBK ']' /** Left bracket */
#define JSTR '"' /** String keeper */
#define JOSP ':' /** Object separator */
#define JVSP ',' /** Value separator */

/*******************************************************************************
 * @brief Append no chars to an other string
 * @param[in] string
 * @param[in] append
 * @param[in] n
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
 * @param[in] buffer
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

        if ((!buffer->is_control) && (tmp == JSTR))
            buffer->skip = !buffer->skip ? BTRU : BFLS;

        if ((buffer->skip && (tmp == JWSP)) ||
            (tmp == JNWL) || (tmp == JRET) || (tmp == JTBS))
            continue;

        buffer->is_control = (tmp == JCTR);
        buffer->buffer[buffer->cursor + buffer->length] = tmp;
        buffer->length++;
    }
}

/*******************************************************************************
 * @brief Increment and read buffer
 * @param[in] buffer
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
 * @brief Check if char is a break char
 * @param[in] c
 * @param[in] breaks
 * @param[in] n
 * @param[in] is_ctrl
 * @return bool_t
 ******************************************************************************/
bool_t check_break(char c, const char *breaks, const int n, bool_t is_ctrl)
{
    for (int i = 0; i < n; ++i)
        if ((!is_ctrl) && (c == breaks[i]))
            return BTRU;

    return BFLS;
}

/*******************************************************************************
 * @brief Read buffer until break an retur allocated string
 * @param[in] buffer
 * @param[in] breaks
 * @param[in] n
 * @param[in] use_ctrl
 * @return string_t
 ******************************************************************************/
string_t read_buffer_until_break(buffer_t *buffer, const char *breaks,
                                 const int n, bool_t use_ctrl)
{
    size_t pos = 0;
    bool_t was_ctrl = BFLS;
    char tmp_string[JBFL];

    string_t result = NULL;
    while (buffer->length > 0)
    {
        if (check_break(buffer->buffer[buffer->cursor], breaks, n, was_ctrl))
            break;

        if (pos >= JBFL - 1)
        {
            result = append_string(result, tmp_string, pos);
            pos = 0;
        }

        was_ctrl = use_ctrl ? (buffer->buffer[buffer->cursor] == JCTR) : BFLS;
        tmp_string[pos] = buffer->buffer[buffer->cursor];
        pos++;

        increment_read_buffer(buffer);
    }

    return append_string(result, tmp_string, pos);
}

/*******************************************************************************
 * @brief Parse a JSON array
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_array(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer)
{
    if (buffer->buffer[buffer->cursor] == JRBK)
        return;

    JSON_t *child = create_json_child_pass(_file, _line, _function, this);

    parse_json_value(_file, _line, _function, child, buffer);
}

/*******************************************************************************
 * @brief Parse a JSON object
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_object(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, buffer_t *buffer)
{
    if (buffer->buffer[buffer->cursor] == JRBC)
        return;

    CHECK_EXPRESSION_PASS(_file, _line, _function,
                          buffer->buffer[buffer->cursor] == JSTR);
    increment_read_buffer(buffer);

    static const char breaks[] = {JSTR};
    static const int n_breaks = sizeof(breaks) / sizeof(char);

    string_t tmp = read_buffer_until_break(buffer, breaks, n_breaks, BFLS);

    CHECK_EXPRESSION_PASS(_file, _line, _function,
                          buffer->buffer[buffer->cursor] == JSTR);
    increment_read_buffer(buffer);

    CHECK_EXPRESSION_PASS(_file, _line, _function,
                          buffer->buffer[buffer->cursor] == JOSP);
    increment_read_buffer(buffer);

    JSON_t *child = create_json_child_pass(_file, _line, _function, this);
    set_json_key_pass(_file, _line, _function, child, tmp);

    DEALLOCATE(tmp);

    parse_json_value(_file, _line, _function, child, buffer);
}

/*******************************************************************************
 * @brief Parse a JSON value
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer)
{
    fill_read_buffer(buffer);
    if (buffer->length == 0)
        return;

    switch (buffer->buffer[buffer->cursor])
    {
    case JLBC:
        increment_read_buffer(buffer);
        set_json_type_pass(_file, _line, _function, this, JSONObject);
        parse_json_object(_file, _line, _function, this, buffer);
        while (buffer->buffer[buffer->cursor] == JVSP)
        {
            increment_read_buffer(buffer);
            parse_json_object(_file, _line, _function, this, buffer);
        }
        CHECK_EXPRESSION_PASS(_file, _line, _function,
                              buffer->buffer[buffer->cursor] == JRBC);
        increment_read_buffer(buffer);
        break;
    case JLBK:
        increment_read_buffer(buffer);
        set_json_type_pass(_file, _line, _function, this, JSONArray);
        parse_json_array(_file, _line, _function, this, buffer);
        while (buffer->buffer[buffer->cursor] == JVSP)
        {
            increment_read_buffer(buffer);
            parse_json_array(_file, _line, _function, this, buffer);
        }
        CHECK_EXPRESSION_PASS(_file, _line, _function,
                              buffer->buffer[buffer->cursor] == JRBK);
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
    case JSTR:
        increment_read_buffer(buffer);
        parse_json_value_string(_file, _line, _function, this, buffer);
        CHECK_EXPRESSION_PASS(_file, _line, _function,
                              buffer->buffer[buffer->cursor] == JSTR);
        increment_read_buffer(buffer);
        break;
    default:
        LOG_ERROR_PASS(_file, _line, _function,
                       "Unknown JSON parse type character (%c)!",
                       buffer->buffer[buffer->cursor]);
        break;
    }
}

/*******************************************************************************
 * @brief Parse a JSON logical
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_boolean(cstring_t _file, int _line, cstring_t _function,
                              JSON_t *this, buffer_t *buffer)
{
    static const char breaks[] = {JSTR, JRBC, JRBK, JVSP};
    static const int n_breaks = sizeof(breaks) / sizeof(char);

    string_t tmp = read_buffer_until_break(buffer, breaks, n_breaks, BFLS);

    CHECK_EXPRESSION_PASS(_file, _line, _function,
                          is_equal(JTRU, tmp) || is_equal(JFLS, tmp));

    set_json_type_pass(_file, _line, _function, this, JSONBoolean);
    STRING_TO(tmp, LogicalType, &this->boolean);

    DEALLOCATE(tmp);
}

/*******************************************************************************
 * @brief Parse a JSON null object
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_null(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, buffer_t *buffer)
{
    static const char breaks[] = {JSTR, JRBC, JRBK, JVSP};
    static const int n_breaks = sizeof(breaks) / sizeof(char);

    string_t tmp = read_buffer_until_break(buffer, breaks, n_breaks, BFLS);
    CHECK_EXPRESSION_PASS(_file, _line, _function, is_equal(JNLL, tmp));

    set_json_type_pass(_file, _line, _function, this, JSONNull);

    DEALLOCATE(tmp);
}

/*******************************************************************************
 * @brief Parse a JSON number
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_number(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer)
{
    static const char breaks[] = {JSTR, JRBC, JRBK, JVSP};
    static const int n_breaks = sizeof(breaks) / sizeof(char);

    string_t tmp = read_buffer_until_break(buffer, breaks, n_breaks, BFLS);

    if (is_digit(tmp))
    {
        set_json_type_pass(_file, _line, _function, this, JSONDigit);
        STRING_TO(tmp, DigitType, &this->digit);
    }
    else if (is_number(tmp))
    {
        set_json_type_pass(_file, _line, _function, this, JSONNumber);
        STRING_TO(tmp, NumberType, &this->number);
    }
    else
    {
        LOG_ERROR_PASS(_file, _line, _function,
                       "Unsupported JSON type digit/number string (%s)!", tmp);
    }

    DEALLOCATE(tmp);
}

/*******************************************************************************
 * @brief Parse a JSON string
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_string(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer)
{
    static const char breaks[] = {JSTR};
    static const int n_breaks = sizeof(breaks) / sizeof(char);

    this->string = read_buffer_until_break(buffer, breaks, n_breaks, BTRU);
    set_json_type_pass(_file, _line, _function, this, JSONString);
}
