/*******************************************************************************
 * @file utils_string.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief Allocate string by copy of string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t allocate_strcpy(cstring_t string);

/*******************************************************************************
 * @brief Allocate string by concatenation of two strings
 * @param[in] string_a
 * @param[in] string_b
 * @return string_t
 ******************************************************************************/
string_t allocate_strcat(cstring_t string_a, cstring_t string_b);

/*******************************************************************************
 * @brief Count number of char occurences in string
 * @param[in] string
 * @param[in] coi
 * @return size_t
 ******************************************************************************/
size_t count_chars(cstring_t string, char coi);

/*******************************************************************************
 * @brief Check if string is a digit
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t is_digit(cstring_t string);

/*******************************************************************************
 * @brief Check if strings are equal
 * @param[in] string_a
 * @param[in] string_b
 * @return bool_t
 ******************************************************************************/
bool_t is_equal(cstring_t string_a, cstring_t string_b);

/*******************************************************************************
 * @brief Check if string is empty
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t is_empty(cstring_t string);

/*******************************************************************************
 * @brief Check if string is a number
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t is_number(cstring_t string);

/*******************************************************************************
 * @brief Length of left/right trimmed string
 * @param[in] string
 * @return size_t
 ******************************************************************************/
size_t len_trim(cstring_t string);

/*******************************************************************************
 * @brief Left trimmed string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t l_trim(string_t string);

/*******************************************************************************
 * @brief Reallocate string by concatenation of two strings
 * @param[in] string_a
 * @param[in] string_b
 * @return string_t
 ******************************************************************************/
string_t reallocate_strcat(string_t string_a, cstring_t string_b);

/*******************************************************************************
 * @brief Replace char in string by replacement
 * @param[in] string
 * @param[in] find
 * @param[in] replace
 ******************************************************************************/
void replace(string_t string, char find, char replace);

/*******************************************************************************
 * @brief Right trimmed string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t r_trim(string_t string);

/*******************************************************************************
 * @brief Maximum length of string array
 * @param[in] strings
 * @param[in] n
 * @return size_t
 ******************************************************************************/
size_t strlen_n(string_t *strings, size_t n);

/*******************************************************************************
 * @brief Left/right trimmed string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t trim(string_t string);

#endif /* UTILS_STRING_H */