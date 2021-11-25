/*******************************************************************************
 * @file print.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-23
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    PRINTF("Hello World!\n");

    FILE *output = fopen("out.dat", "w");
    set_stdout(output);

    PRINTF("Hello World!\n");
    printf_r_sep('.');
    printf_r_sep_title('.', "Test title");

    RESET_STDOUT();
    fclose(output);

    return 0;
}