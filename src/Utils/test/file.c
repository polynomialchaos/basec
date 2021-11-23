/*******************************************************************************
 * @file file.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    string_t file_name = "out.dat";
    FILE *output = create_file(file_name);
    fclose(output);

    CHECK_EXPRESSION(file_exists(file_name) == BTRU);

    output = open_file(file_name);
    fclose(output);

    return 0;
}