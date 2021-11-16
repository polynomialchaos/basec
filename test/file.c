/*******************************************************************************
 * @file file.c
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
    FILE *output = create_file("out2.dat");
    fclose(output);

    output = open_file("out2.dat");
    fclose(output);

    return 0;
}