/*******************************************************************************
 * @file memory.c
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
    double *tmp = ALLOCATE(sizeof(double) * 12);
    CHECK_EXPRESSION(tmp != NULL);

    tmp = REALLOCATE(tmp, sizeof(double) * 12);
    CHECK_EXPRESSION(tmp != NULL);

    DEALLOCATE(tmp);
    CHECK_EXPRESSION(tmp == NULL);

    return 0;
}