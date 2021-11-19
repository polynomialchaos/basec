/*******************************************************************************
 * @file json_module.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef JSON_MODULE_H
#define JSON_MODULE_H

#include "basec/basec_macro.h"
#include "basec/basec_type.h"
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief A macro to create child in JSON object
 ******************************************************************************/
#define create_json_child(this) create_json_child_pass(__PASS__, (this))

/*******************************************************************************
 * @brief A macro to get a JSON object by path
 ******************************************************************************/
#define get_json_object_by_path(this, path) \
    get_json_object_by_path_pass(__PASS__, (this), (path))

/*******************************************************************************
 * @brief A macro to get a JSON object value
 ******************************************************************************/
#define get_json_value(this, type, value) \
    get_json_value_i_pass(__PASS__, (this), (type), (0), (value))

/*******************************************************************************
 * @brief A macro to get a JSON object value at index i
 ******************************************************************************/
#define get_json_value_i(this, type, i, value) \
    get_json_value_i_pass(__PASS__, (this), (type), (i), (value))

/*******************************************************************************
 * @brief A macro to get all JSON object values
 ******************************************************************************/
#define get_json_value_n(this, type, value, n) \
    get_json_value_n_pass(__PASS__, (this), (type), (value), (n))

/*******************************************************************************
 * @brief A macro to get a JSON object value and pass file, line and function
 ******************************************************************************/
#define get_json_value_pass(_file, _line, _function, this, type, value) \
    get_json_value_i_pass((_file), (_line), (_function),                \
                          (this), (type), (0), (value))

/*******************************************************************************
 * @brief A macro to parse a JSON file
 ******************************************************************************/
#define parse_json_file(path) parse_json_file_pass(__PASS__, (path))

/*******************************************************************************
 * @brief A macro to parse a JSON string
 ******************************************************************************/
#define parse_json_string(string) parse_json_string_pass(__PASS__, (string))

/*******************************************************************************
 * @brief A macro to print JSON object
 ******************************************************************************/
#define print_json_object(this, file_pointer) \
    print_json_object_pass(__PASS__, (this), (file_pointer), (0))

/*******************************************************************************
 * @brief A macro to print JSON object with indent
 ******************************************************************************/
#define print_json_object_indent(this, file_pointer, indent) \
    print_json_object_pass(__PASS__, (this), (file_pointer), (indent))

/*******************************************************************************
 * @brie A macro to print JSON object as continous string
 ******************************************************************************/
#define print_json_object_short(this, file_pointer) \
    print_json_object_pass(__PASS__, (this), (file_pointer), (-1))

/*******************************************************************************
 * @brief A macro to set a JSON object by path
 ******************************************************************************/
#define set_json_object_by_path(this, path) \
    set_json_object_by_path_pass(__PASS__, (this), (path))

/*******************************************************************************
 * @brief A macro to set the key for a JSON object
 ******************************************************************************/
#define set_json_key(this, key) set_json_key_pass(__PASS__, (this), (key))

/*******************************************************************************
 * @brief A macro to set the type for a JSON object
 ******************************************************************************/
#define set_json_type(this, type) set_json_type_pass(__PASS__, (this), (type))

/*******************************************************************************
 * @brief A macro to set the value for a JSON object
 ******************************************************************************/
#define set_json_value(this, type, value) \
    set_json_value_i_pass(__PASS__, (this), (type), (value), (0))

/*******************************************************************************
 * @brief A macro to set the value at index i for a JSON object
 ******************************************************************************/
#define set_json_value_i(this, type, value, i) \
    set_json_value_i_pass(__PASS__, (this), (type), (value), (i))

/*******************************************************************************
 * @brief A macro to set all values for a JSON object
 ******************************************************************************/
#define set_json_value_n(this, type, value, n) \
    set_json_value_n_pass(__PASS__, (this), (type), (value), (n))

/*******************************************************************************
 * @brief A macro to set the value for a JSON object
 * and pass file, line and function
 ******************************************************************************/
#define set_json_value_pass(_file, _line, _function, this, type, value) \
    set_json_value_i_pass((_file), (_line), (_function),                \
                          (this), (type), (value), (0))

/*******************************************************************************
 * @brief JSON type enumeration
 ******************************************************************************/
typedef enum JSONType
{
    JSONNull,       /** Null JSON type */
    JSONObject,     /** Object JSON type */
    JSONArray,      /** Array JSON type */
    JSONBoolean,    /** Booelan JSON type */
    JSONDigit,      /** Digit JSON type */
    JSONNumber,     /** Number JSON type */
    JSONString,     /** String JSON type */
    _JSONUndefined, /** Undefined JSON type */
    _json_type_max
} json_type_t;

/*******************************************************************************
 * @brief JSON type structure
 ******************************************************************************/
typedef struct JSON
{
    string_t key;        /** JSON object key */
    struct JSON *parent; /** JSON object parent */
    list_t *childs;      /** JSON object childs */

    json_type_t type; /** JSON object type */
    bool_t boolean;   /** JSON object boolan value */
    int digit;        /** JSON object digit value */
    double number;    /** JSON object number value */
    string_t string;  /** JSON object string value */
} JSON_t;

/*******************************************************************************
 * @brief Create a JSON object child and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @return JSON_t*
 ******************************************************************************/
JSON_t *create_json_child_pass(cstring_t _file, int _line, cstring_t _function,
                               JSON_t *this);

/*******************************************************************************
 * @brief Create a JSON object
 * @return JSON_t*
 ******************************************************************************/
JSON_t *create_json_object();

/*******************************************************************************
 * @brief Count number of JSON object childs
 * @param[in] this
 * @return size_t
 ******************************************************************************/
size_t count_json_childs(JSON_t *this);

/*******************************************************************************
 * @brief Deallocate a JSON object
 * @param[in] this
 ******************************************************************************/
void free_json_object(void *this);

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
                                     JSON_t *this, cstring_t path);

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
                           size_t i, void *value);

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
                           void **value, size_t *n);

/*******************************************************************************
 * @brief Parse a JOSN file and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *parse_json_file_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path);

/*******************************************************************************
 * @brief Parse a JOSN string and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] string
 * @return JSON_t*
 ******************************************************************************/
JSON_t *parse_json_string_pass(cstring_t _file, int _line, cstring_t _function,
                               string_t string);

/*******************************************************************************
 * @brief Print a JSON object and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] file_pointer
 * @param[in] indent
 ******************************************************************************/
void print_json_object_pass(cstring_t _file, int _line, cstring_t _function,
                            JSON_t *this, FILE *file_pointer, int indent);

/*******************************************************************************
 * @brief Set the JSON object key and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] key
 ******************************************************************************/
void set_json_key_pass(cstring_t _file, int _line, cstring_t _function,
                       JSON_t *this, cstring_t key);

/*******************************************************************************
 * @brief Se a JSON object by path and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] path
 * @return JSON_t*
 ******************************************************************************/
JSON_t *set_json_object_by_path_pass(cstring_t _file, int _line,
                                     cstring_t _function,
                                     JSON_t *this, cstring_t path);

/*******************************************************************************
 * @brief Set the JSON object type and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 ******************************************************************************/
void set_json_type_pass(cstring_t _file, int _line, cstring_t _function,
                        JSON_t *this, json_type_t type);

/*******************************************************************************
 * @brief Set a JSON value at index i and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 * @param[in] value
 * @param[in] i
 ******************************************************************************/
void set_json_value_i_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t i);

/*******************************************************************************
 * @brief Set a JSON value vector and pass file, line, function
*  @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] this
 * @param[in] type
 * @param[in] value
 * @param[in] n
 ******************************************************************************/
void set_json_value_n_pass(cstring_t _file, int _line, cstring_t _function,
                           JSON_t *this, json_type_t type,
                           void *value, size_t n);

#endif /* JSON_MODULE_H */