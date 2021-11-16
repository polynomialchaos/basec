/*******************************************************************************
 * @file string.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include <ctype.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Allocate string by copy of string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t allocate_strcpy(cstring_t string)
{
    size_t length = strlen(string);
    string_t tmp = ALLOCATE(sizeof(char) * (length + 1));
    strcpy(tmp, string);

    return tmp;
}

/*******************************************************************************
 * @brief Allocate string by concatenation of two strings
 * @param[in] string_a
 * @param[in] string_b
 * @return string_t
 ******************************************************************************/
string_t allocate_strcat(cstring_t string_a, cstring_t string_b)
{
    size_t length = strlen(string_a) + strlen(string_b);
    string_t tmp = ALLOCATE(sizeof(char) * (length + 1));
    strcpy(tmp, string_a);
    strcat(tmp, string_b);

    return tmp;
}

/*******************************************************************************
 * @brief Count number of char occurences in string
 * @param[in] string
 * @param[in] coi
 * @return size_t
 ******************************************************************************/
size_t count_chars(cstring_t string, char coi)
{
    size_t tmp = 0;
    for (int i = 0; string[i]; ++i)
        if (string[i] == coi)
            tmp++;

    return tmp;
}

/*******************************************************************************
 * @brief Check if string is a digit
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t is_digit(cstring_t string)
{
    if (string == NULL)
        return FALSE;
    if (string[0] == NULL_CHAR)
        return FALSE;

    string_t tmp;
    strtol(string, &tmp, 10);
    return (*tmp == NULL_CHAR);
}

/*******************************************************************************
 * @brief Check if strings are equal
 * @param[in] string_a
 * @param[in] string_b
 * @return bool_t
 ******************************************************************************/
bool_t is_equal(cstring_t string_a, cstring_t string_b)
{
    if ((string_a == NULL) || (string_b == NULL))
        return (string_a == string_b);

    return (strcmp(string_a, string_b) == 0);
}

/*******************************************************************************
 * @brief Check if string is empty
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t is_empty(cstring_t string)
{
    return (len_trim(string) == 0);
}

/*******************************************************************************
 * @brief Check if string is a number
 * @param[in] string
 * @return bool_t
 ******************************************************************************/
bool_t is_number(cstring_t string)
{
    if (string == NULL)
        return FALSE;
    if (string[0] == NULL_CHAR)
        return FALSE;
    if (is_digit(string))
        return FALSE;

    string_t tmp;
    strtod(string, &tmp);
    return (*tmp == NULL_CHAR);
}

/*******************************************************************************
 * @brief Length of left/right trimmed string
 * @param[in] string
 * @return size_t
 ******************************************************************************/
size_t len_trim(cstring_t string)
{
    if (string == NULL)
        return 0;
    if (string[0] == NULL_CHAR)
        return 0;

    string_t tmp = allocate_strcpy(string);
    size_t str_len = strlen(trim(tmp));
    DEALLOCATE(tmp);

    return str_len;
}

/*******************************************************************************
 * @brief Left trimmed string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t l_trim(string_t string)
{
    while (isspace(*string))
        string++;

    return string;
}

/*******************************************************************************
 * @brief Reallocate string by concatenation of two strings
 * @param[in] string_a
 * @param[in] string_b
 * @return string_t
 ******************************************************************************/
string_t reallocate_strcat(string_t string_a, cstring_t string_b)
{
    size_t length = strlen(string_a) + strlen(string_b);
    string_a = REALLOCATE(string_a, sizeof(char) * (length + 1));
    strcat(string_a, string_b);

    return string_a;
}

/*******************************************************************************
 * @brief Replace char in string by replacement
 * @param[in] string
 * @param[in] find
 * @param[in] replace
 ******************************************************************************/
void replace(string_t string, char find, char replace)
{
    for (int i = 0; string[i]; ++i)
        if (string[i] == find)
            string[i] = replace;
}

/*******************************************************************************
 * @brief Right trimmed string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t r_trim(string_t string)
{
    if (string == NULL)
        return string;
    if (string[0] == NULL_CHAR)
        return string;

    string_t pos = string + strlen(string) - 1;
    while (pos > string && isspace((unsigned char)*pos))
        pos--;

    // Write new null terminator character
    pos[1] = NULL_CHAR;

    return string;
}

/*******************************************************************************
 * @brief Maximum length of string array
 * @param[in] strings
 * @param[in] n
 * @return size_t
 ******************************************************************************/
size_t strlen_n(string_t *strings, size_t n)
{
    size_t max_len = 0;
    for (size_t i = 0; i < n; ++i)
        max_len = MAX_T(max_len, strlen(strings[i]));

    return max_len;
}

/*******************************************************************************
 * @brief Left/right trimmed string
 * @param[in] string
 * @return string_t
 ******************************************************************************/
string_t trim(string_t string)
{
    return l_trim(r_trim(string));
}