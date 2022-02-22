/*******************************************************************************
 * @file json_private.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef JSON_PRIVATE_H
#define JSON_PRIVATE_H

#include "basec/json_module.h"

#define JERR "Unknown JSON data type (%d)!" /** Unknown type string */
#define JTRU "true"                         /** JSON BTRU string */
#define JFLS "false"                        /** JSON BFLS string */
#define JNLL "null"                         /** JSON null string */

#define JBFL 2048 /** Maximum buffer length */

/*******************************************************************************
 * @brief buffer structure
 ******************************************************************************/
typedef struct Buffer
{
    char buffer[JBFL]; /** Buffer array */
    size_t cursor;     /** Buffer cursor in array */
    int length;        /** Buffer length */
    bool_t skip;       /** Skip flag */
    bool_t is_control; /** Control flag */
    bool_t is_file;    /** File flag */
    int is_eof;        /** EOF flag */
    union
    {
        FILE *file;   /** File pointer */
        char *string; /** String array */
    };
} buffer_t;

/*******************************************************************************
 * @brief Parse a JSON array
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_array(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON object
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_object(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON value
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON logical
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_boolean(cstring_t _file, int _line, cstring_t _function,
                              JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON null object
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_null(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON number
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_number(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON string
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] buffer
 ******************************************************************************/
void parse_json_value_string(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer);

#endif /* JSON_PRIVATE_H */