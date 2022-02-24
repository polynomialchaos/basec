/*******************************************************************************
 * @file print.c
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
    BM_PRINT("Hello World!\n");

    FILE *output = fopen("out.dat", "w");
    set_stdout(output);

    BM_PRINT("Hello World!\n");
    printf_r_sep('.');
    printf_r_sep_title('.', "Test title");

    BM_RESET_STDOUT();
    fclose(output);

    return 0;
}