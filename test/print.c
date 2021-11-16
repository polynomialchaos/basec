/*******************************************************************************
 * @file print.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/basec_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    printf_r("Hello World!\n");

    FILE *output = fopen("out.dat", "w");
    set_stdout(output);

    printf_r("Hello World!\n");
    printf_r_sep('.');
    printf_r_sep_title('.', "Test title");

    reset_stdout();
    fclose(output);

    return 0;
}