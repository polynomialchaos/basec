/*******************************************************************************
 * @file STRING_TO.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include <ctype.h>
#include "utils_private.h"

#define USLB '['       /** String vector left bracket */
#define USRB ']'       /** String vector right bracket */
#define USVD ","       /** String vector delimiter */
#define UCVD (*(USVD)) /** Char vector delimiter */

/** String conversion flag strings */
cstring_t conversion_flag_strings[_sc_flag_max] = {
    "String conversion successfull",
    "String is pointing to null or is empty",
    "String is too long",
    "Missing brackets",
    "Unknown data type"};

/** String to bool_t conversion keywords */
cstring_t bool_keywords[] = {"t", "true", "on", "1"};

/** Number of string to bool_t conversion keywords */
size_t n_bool_keywords =
    sizeof(bool_keywords) / sizeof(cstring_t);

/** String data type sizes in bytes */
const size_t string_datatype_bytes[_sc_type_max] = {
    sizeof(bool_t), sizeof(int), sizeof(double), sizeof(string_t)};

/*******************************************************************************
 * @brief Decode the given string conversion flag
 * @param[in] error
 * @return cstring_t
 ******************************************************************************/
cstring_t conversion_flag_string(sc_flag_t flag)
{
    return conversion_flag_strings[flag];
}

/*******************************************************************************
 * @brief Convert string to boolean variable data type
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t string_to_bool(cstring_t string)
{
    if (string == NULL)
        return 0;
    if (string[0] == BNCH)
        return 0;

    // create a copy of the string to perform lower case transformation
    string_t tmp = allocate_strcpy(string);
    for (size_t i = 0; tmp[i]; ++i)
        tmp[i] = tolower(tmp[i]);

    // check if string is a True place-holder
    bool_t is_true = BFLS;
    for (size_t i = 0; i < n_bool_keywords; ++i)
        if (is_equal(tmp, bool_keywords[i]))
        {
            is_true = BTRU;
            break;
        }

    DEALLOCATE(tmp);
    return is_true;
}

/*******************************************************************************
 * @brief Convert string at ith position
 * @param[in] string
 * @param[in] type
 * @param[in] i
 * @param[out] value
 * @return sc_flag_t
 ******************************************************************************/
sc_flag_t string_to_i(cstring_t string, sc_type_t type, size_t i, void *value)
{
    if (is_empty(string))
        return StringNullEmpty;

    sc_flag_t error = StringOK;

    switch (type)
    {
    case LogicalType:
        ((bool_t *)value)[i] = string_to_bool(string);
        break;
    case DigitType:
        ((int *)value)[i] = atoi(string);
        break;
    case NumberType:
        ((double *)value)[i] = atof(string);
        break;
    case StringType:
        ((string_t *)value)[i] = allocate_strcpy(string);
        break;
    default:
        error = StringUndefined;
        break;
    }

    return error;
}

/*******************************************************************************
 * @brief Convert string to array variables
 * @param[in] string
 * @param[in] type
 * @param[out] value
 * @param[out] n
 * @return sc_flag_t
 ******************************************************************************/
sc_flag_t string_to_n_wo_check(cstring_t string, sc_type_t type,
                               void **value, size_t *n)
{
    if (is_empty(string))
        return StringNullEmpty;

    size_t length = strlen(string);
    if ((string[0] != USLB) || (string[length - 1] != USRB))
        return StringMissingBraces;

    (*n) = count_chars(string, UCVD) + 1;
    (*value) = ALLOCATE(string_datatype_bytes[type] * (*n));

    // create a copy of the string to perform the string truncation
    string_t tmp = allocate_strcpy(string);

    replace(tmp, USLB, ' ');
    replace(tmp, USRB, ' ');

    string_t element = strtok(trim(tmp), USVD);

    sc_flag_t error = StringOK;

    for (size_t i = 0; i < (*n); ++i)
    {
        error = string_to_i(element, type, i, *value);
        if (error != StringOK)
            break;
        element = strtok(NULL, USVD);
    }

    DEALLOCATE(tmp);
    return error;
}

/*******************************************************************************
 * @brief Convert string to variable
 * @param[in] string
 * @param[in] type
 * @param[out] value
 * @return sc_flag_t
 ******************************************************************************/
sc_flag_t string_to_wo_check(cstring_t string, sc_type_t type, void *value)
{
    return string_to_i(string, type, 0, value);
}