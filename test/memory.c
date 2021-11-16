/*******************************************************************************
 * @file memory.c
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
    double *tmp = ALLOCATE(sizeof(double) * 12);
    check_expression(tmp != NULL);

    tmp = REALLOCATE(tmp, sizeof(double) * 12);
    check_expression(tmp != NULL);

    DEALLOCATE(tmp);
    check_expression(tmp == NULL);

    return 0;
}