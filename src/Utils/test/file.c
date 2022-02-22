/*******************************************************************************
 * @file file.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Main function
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