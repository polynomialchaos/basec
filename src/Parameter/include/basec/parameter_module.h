/*******************************************************************************
 * @file parameter_module.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef PARAMETER_MODULE_H
#define PARAMETER_MODULE_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to get a parameter
 ******************************************************************************/
#define get_parameter(path, type, value) \
    get_parameter_pass(__PASS__, (path), (type), (value))

/*******************************************************************************
 * @brief A macro to get a vector parameter count
 ******************************************************************************/
#define get_parameter_count(path) get_parameter_count_pass(__PASS__, (path))

/*******************************************************************************
 * @brief A macro to get a vector parameter
 ******************************************************************************/
#define get_parameter_n(path, type, value, n) \
    get_parameter_n_pass(__PASS__, (path), (type), (value), (n))

/*******************************************************************************
 * @brief A macro to set a parameter
 ******************************************************************************/
#define set_parameter(path, type, value, description, options, n_options) \
    set_parameter_pass(__PASS__, (path), (type), (value),                 \
                       (description), (options), (n_options))

/*******************************************************************************
 * @brief A macro to set a vector parameter
 ******************************************************************************/
#define set_parameter_n(path, type, value, n, description, options, n_options) \
    set_parameter_n_pass(__PASS__, (path), (type), (value), (n),               \
                         (description), (options), (n_options))

/*******************************************************************************
 * @brief A macro to check if parameter exists
 ******************************************************************************/
#define parameter_exists(path) parameter_exists_pass(__PASS__, (path))

/*******************************************************************************
 * @brief Parameter type enumeration
 ******************************************************************************/
typedef enum ParameterType
{
    ParameterBool,   /** Boolean parameter type */
    ParameterDigit,  /** Digit parameter type */
    ParameterNumber, /** Number parameter type */
    ParameterString, /** String parameter type */
    _parameter_type_max
} parameter_type_t;

/*******************************************************************************
 * @brief Flush the user defaults to file
 * @param[in] file_name
 ******************************************************************************/
void flush_user_defaults(cstring_t file_name);

/*******************************************************************************
 * @brief Free the parameters
 ******************************************************************************/
void free_parameters();

/*******************************************************************************
 * @brief Get a parameter and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @param type
 * @param value
 ******************************************************************************/
void get_parameter_pass(cstring_t _file, int _line, cstring_t _function,
                        cstring_t path, parameter_type_t type, void *value);

/*******************************************************************************
 * @brief Get a vector parameter count and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @return int
 ******************************************************************************/
int get_parameter_count_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path);

/*******************************************************************************
 * @brief Get a vector parameter and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @param value
 * @param type
 * @param n
 ******************************************************************************/
void get_parameter_n_pass(cstring_t _file, int _line, cstring_t _function,
                          cstring_t path, void **value,
                          parameter_type_t type, size_t *n);

/*******************************************************************************
 * @brief Check if parameter exists and pass file, line, function
 * @param _file
 * @param _line
 * @param _function
 * @param path
 * @return int
 ******************************************************************************/
bool_t parameter_exists_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path);

/*******************************************************************************
 * @brief Print the user defaults to stdout
 ******************************************************************************/
void print_user_defaults();

/*******************************************************************************
 * @brief Print the user inputs to stdout
 ******************************************************************************/
void print_user_inputs();

/*******************************************************************************
 * @brief Flush the user inputs to file
 * @param[in] file_name
 ******************************************************************************/
void read_user_inputs(cstring_t file_name);

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
                        void *options, size_t n_options);

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
                          void *options, size_t n_options);

#endif /* PARAMETER_MODULE_H */