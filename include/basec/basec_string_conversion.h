/*******************************************************************************
 * @file basecstring_to.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef BASE_STRING_CONVERSION_H
#define BASE_STRING_CONVERSION_H

// #include <stdlib.h>
#include "basec/basec_type.h"

/** String conversion failed message */
#define UTILITIES_STRING_CON "String conversion of '%s' failed (%s)!"

/*******************************************************************************
 * @brief A macro to convert a string to a value
 ******************************************************************************/
#define string_to(string, type, value) (                           \
    {                                                              \
        int error = string_to_wo_check((string), (type), (value)); \
        if (error != StringOK)                                     \
            log_error(UTILITIES_STRING_CON, (#string),             \
                      string_conversion_flag(error));              \
    })

/*******************************************************************************
 * @brief A macro to convert a string to a value array
 ******************************************************************************/
#define string_to_n(string, type, value, n) (                             \
    {                                                                     \
        int error = string_to_n_wo_check((string), (type), (value), (n)); \
        if (error != StringOK)                                            \
            log_error(UTILITIES_STRING_CON, (#string),                    \
                      string_conversion_flag(error));                     \
    })

/*******************************************************************************
 * @brief String conversion flag enumeration
 ******************************************************************************/
typedef enum StringConversion
{
    StringOK,            /** String conversion OK */
    StringNull,          /** String is NULL */
    StringEmpty,         /** String empty */
    StringToLong,        /** String too long */
    StringMissingBraces, /** Missing braces is string */
    StringUndefined,     /** String data type is undefined */
    _string_conversion_max
} string_conversion_t;

/*******************************************************************************
 * @brief String data type enumeration
 ******************************************************************************/
typedef enum StringDatatype
{
    BooleanString, /** Boolean type */
    DigitString,   /** Digit type */
    NumberString,  /** Number type */
    StringString,  /** String type */
    _string_datatype_max
} string_datatype_t;

/*******************************************************************************
 * @brief Decode the given string conversion flag
 * @param[in] error
 * @return cstring_t
 ******************************************************************************/
cstring_t string_conversion_flag(string_conversion_t flag);

/*******************************************************************************
 * @brief Convert string to boolean variable data type
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t string_to_bool(cstring_t string);

/*******************************************************************************
 * @brief Convert string to array variables
 * @param[in] string
 * @param[in] type
 * @param[out] value
 * @param[out] n
 * @return string_error_t
 ******************************************************************************/
string_conversion_t string_to_n_wo_check(cstring_t string,
                                         string_datatype_t type, void **value,
                                         size_t *n);

/*******************************************************************************
 * @brief Convert string to variable
 * @param[in] string
 * @param[in] type
 * @param[out] value
 * @return string_error_t
 ******************************************************************************/
string_conversion_t string_to_wo_check(cstring_t string,
                                       string_datatype_t type, void *value);

#endif /* BASE_STRING_CONVERSION_H */