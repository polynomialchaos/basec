/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/parameter_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    int value = 12;
    int values[] = {1, 2, 3, 5, 12};

    set_parameter("General/a/b/c/d", ParameterDigit, &value, NULL, NULL, 0);
    set_parameter("General/a/b/c/e", ParameterDigit, &value, "Test", NULL, 0);
    set_parameter("General/a/b/c/f", ParameterDigit, &value, "Test", &values[0], 1);

    print_user_defaults();

    get_parameter("General/a/b/c/d", ParameterDigit, &value);
    get_parameter("General/a/b/c/e", ParameterDigit, &value);
    get_parameter("General/a/b/c/f", ParameterDigit, &value);

    free_parameters();

    return 0;
}