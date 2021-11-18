/*******************************************************************************
 * @file parameter.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
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
    print_json_object(user_defaults, file);
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
        DEALLOCATE(user_defaults);
    }

    if (user_inputs != NULL)
    {
        free_json_object(user_inputs);
        DEALLOCATE(user_inputs);
    }
}

/*******************************************************************************
 * @brief Print the user defaults to stdout
 ******************************************************************************/
void print_user_defaults()
{
    print_json_object(user_defaults, get_stdout());
}

/*******************************************************************************
 * @brief Print the user inputs to stdout
 ******************************************************************************/
void print_user_inputs()
{
    print_json_object(user_inputs, get_stdout());
}

/*******************************************************************************
 * @brief Flush the user inputs to file
 * @param[in] file_name
 ******************************************************************************/
void read_user_inputs(cstring_t file_name)
{
    user_inputs = parse_json_file(file_name);
}