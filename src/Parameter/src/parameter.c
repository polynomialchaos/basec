/*******************************************************************************
 * @file parameter.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "parameter_private.h"

JSON_t *user_defaults; /** Static field for user defaults */
JSON_t *user_inputs;   /** Static field for user inputs */

/** Parameter type sizes */
int as_json_type[_parameter_type_max] = {
    JSONBoolean, JSONDigit, JSONNumber, JSONString};

/*******************************************************************************
 * @brief Flush the user defaults to file
 * @param[in] file_name
 ******************************************************************************/
void flush_user_defaults(cstring_t file_name)
{
    FILE *file = create_file(file_name);
    BM_PRINT_JSON_OBJECT(user_defaults, file);
    close_file(file);
}

/*******************************************************************************
 * @brief Free the parameters
 ******************************************************************************/
void free_parameters()
{
    if (user_defaults != NULL)
    {
        free_json_object(user_defaults);
        BM_DEALLOCATE(user_defaults);
    }

    if (user_inputs != NULL)
    {
        free_json_object(user_inputs);
        BM_DEALLOCATE(user_inputs);
    }
}

/*******************************************************************************
 * @brief Print the user defaults to stdout
 ******************************************************************************/
void print_user_defaults()
{
    BM_PRINT_JSON_OBJECT(user_defaults, get_stdout());
}

/*******************************************************************************
 * @brief Print the user inputs to stdout
 ******************************************************************************/
void print_user_inputs()
{
    BM_PRINT_JSON_OBJECT(user_inputs, get_stdout());
}

/*******************************************************************************
 * @brief Flush the user inputs to file
 * @param[in] file_name
 ******************************************************************************/
void read_user_inputs(cstring_t file_name)
{
    user_inputs = BM_PARSE_JSON_FILE(file_name);
}