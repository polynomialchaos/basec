/*******************************************************************************
 * @file math_functions.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include "basec/utils_module.h"
#include "math_private.h"

/*******************************************************************************
 * @brief Return the factorial of a value
 * @param[in] n
 * @return int
 ******************************************************************************/
int factorial(int n)
{
    check_expression(n >= 0);

    int factorial = 1;
    for (int i = 1; i <= n; ++i)
    {
        factorial *= i;
    }

    check_expression(factorial > 0);
    return factorial;
}