/*******************************************************************************
 * @file basecstring_to.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef UTILS_STRING_CONVERSION_H
#define UTILS_STRING_CONVERSION_H

#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/** String conversion failed message */
#define USCF "String conversion of '%s' failed (%s)!"

/*******************************************************************************
 * @brief A macro to convert a string to a value
 ******************************************************************************/
#define STRING_TO(string, type, value) (                               \
    {                                                                  \
        int error = string_to_wo_check((string), (type), (value));     \
        if (error != StringOK)                                         \
            LOG_ERROR(USCF, (#string), conversion_flag_string(error)); \
    })

/*******************************************************************************
 * @brief A macro to convert a string to a value array
 ******************************************************************************/
#define STRING_TO_N(string, type, value, n) (                             \
    {                                                                     \
        int error = string_to_n_wo_check((string), (type), (value), (n)); \
        if (error != StringOK)                                            \
            LOG_ERROR(USCF, (#string), conversion_flag_string(error));    \
    })

/*******************************************************************************
 * @brief String conversion enumeration
 ******************************************************************************/
typedef enum SCFlag
{
    StringOK,            /** String conversion OK */
    StringNullEmpty,     /** String is NULL or empty */
    StringToLong,        /** String too long */
    StringMissingBraces, /** Missing braces is string */
    StringUndefined,     /** String data type is undefined */
    _sc_flag_max
} sc_flag_t;

/*******************************************************************************
 * @brief String datatype enumeration
 ******************************************************************************/
typedef enum SCType
{
    LogicalType, /** Boolean type */
    DigitType,   /** Digit type */
    NumberType,  /** Number type */
    StringType,  /** String type */
    _sc_type_max
} sc_type_t;

/*******************************************************************************
 * @brief Decode the given string conversion flag
 * @param[in] error
 * @return cstring_t
 ******************************************************************************/
cstring_t conversion_flag_string(sc_flag_t flag);

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
 * @return sc_flag_t
 ******************************************************************************/
sc_flag_t string_to_n_wo_check(cstring_t string, sc_type_t type,
                               void **value, size_t *n);

/*******************************************************************************
 * @brief Convert string to variable
 * @param[in] string
 * @param[in] type
 * @param[out] value
 * @return sc_flag_t
 ******************************************************************************/
sc_flag_t string_to_wo_check(cstring_t string, sc_type_t type, void *value);

#endif /* UTILS_STRING_CONVERSION_H */