/*******************************************************************************
 * @file time.c
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
    list_t test;
    list_init(&test, NULL);

    int test_val = 12;

    list_append(&test, sizeof(int), &test_val);
    list_prepend(&test, sizeof(int), &test_val);
    list_append(&test, sizeof(int), &test_val);
    list_append(&test, sizeof(int), &test_val);
    list_append(&test, sizeof(int), &test_val);
    list_append(&test, sizeof(int), &test_val);
    list_prepend(&test, sizeof(int), &test_val);
    list_prepend(&test, sizeof(int), &test_val);

    list_deallocate(&test);

    return 0;
}