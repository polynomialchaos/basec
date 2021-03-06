/*******************************************************************************
 * @file parameter_module.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef PARAMETER_MODULE_H
#define PARAMETER_MODULE_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to get a parameter
 ******************************************************************************/
#define BM_GET_PARAMETER(path, type, value) \
    get_parameter_pass(__PASS__, (path), (type), (value))

/*******************************************************************************
 * @brief A macro to get a vector parameter count
 ******************************************************************************/
#define BM_GET_PARAMETER_COUNT(path) get_parameter_count_pass(__PASS__, (path))

/*******************************************************************************
 * @brief A macro to get a vector parameter
 ******************************************************************************/
#define BM_GET_PARAMETER_N(path, type, value, n) \
    get_parameter_n_pass(__PASS__, (path), (type), (value), (n))

/*******************************************************************************
 * @brief A macro to set a parameter
 ******************************************************************************/
#define BM_SET_PARAMETER(path, type, value, description, options, n_options) \
    set_parameter_pass(__PASS__, (path), (type), (value),                    \
                       (description), (options), (n_options))

/*******************************************************************************
 * @brief A macro to set a vector parameter
 ******************************************************************************/
#define BM_SET_PARAMETER_N(path, type, value, n,                 \
                           description, options, n_options)      \
    set_parameter_n_pass(__PASS__, (path), (type), (value), (n), \
                         (description), (options), (n_options))

/*******************************************************************************
 * @brief A macro to check if parameter exists
 ******************************************************************************/
#define BM_PARAMETER_EXISTS(path) parameter_exists_pass(__PASS__, (path))

/*******************************************************************************
 * @brief Parameter type enumeration
 ******************************************************************************/
typedef enum ParameterType
{
    LogicalParameter, /** Boolean parameter type */
    DigitParameter,   /** Digit parameter type */
    NumberParameter,  /** Number parameter type */
    StringParameter,  /** String parameter type */
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
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] type
 * @param[out] value
 ******************************************************************************/
void get_parameter_pass(cstring_t _file, int _line, cstring_t _function,
                        cstring_t path, parameter_type_t type, void *value);

/*******************************************************************************
 * @brief Get a vector parameter count and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @return int
 ******************************************************************************/
int get_parameter_count_pass(cstring_t _file, int _line, cstring_t _function,
                             cstring_t path);

/*******************************************************************************
 * @brief Get a vector parameter and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] type
 * @param[out] value
 * @param[out] n
 ******************************************************************************/
void get_parameter_n_pass(cstring_t _file, int _line, cstring_t _function,
                          cstring_t path, parameter_type_t type,
                          void **value, size_t *n);

/*******************************************************************************
 * @brief Check if parameter exists and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
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
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] type
 * @param[in] value
 * @param[in] description
 * @param[in] options
 * @param[in] n_options
 ******************************************************************************/
void set_parameter_pass(cstring_t _file, int _line, cstring_t _function,
                        cstring_t path, parameter_type_t type,
                        void *value, cstring_t description,
                        void *options, size_t n_options);

/*******************************************************************************
 * @brief Set a vector parameter and pass file, line, function
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] type
 * @param[in] value
 * @param[in] n
 * @param[in] description
 * @param[in] options
 * @param[in] n_options
 ******************************************************************************/
void set_parameter_n_pass(cstring_t _file, int _line, cstring_t _function,
                          cstring_t path, parameter_type_t type,
                          void *value, size_t n, cstring_t description,
                          void *options, size_t n_options);

#endif /* PARAMETER_MODULE_H */