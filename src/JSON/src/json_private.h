/*******************************************************************************
 * @file json_private.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef JSON_PRIVATE_H
#define JSON_PRIVATE_H

#include "basec/utils_module.h"
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
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_array(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON object
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_object(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON value
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value(cstring_t _file, int _line, cstring_t _function,
                      JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON logical
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_boolean(cstring_t _file, int _line, cstring_t _function,
                              JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON null object
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_null(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON number
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_number(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer);

/*******************************************************************************
 * @brief Parse a JSON string
 * @param _file
 * @param _line
 * @param _function
 * @param this
 * @param buffer
 ******************************************************************************/
void parse_json_value_string(cstring_t _file, int _line, cstring_t _function,
                             JSON_t *this, buffer_t *buffer);

#endif /* JSON_PRIVATE_H */