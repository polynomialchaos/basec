/*******************************************************************************
 * @file string.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
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
    string_t test_string = allocate_strcpy("Hallo du .....");
    printf_r("%s\n", test_string);
    DEALLOCATE(test_string);

    return 0;
}