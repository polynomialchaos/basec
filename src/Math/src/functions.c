/*******************************************************************************
 * @file math_functions.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
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
    CHECK_EXPRESSION(n >= 0);

    int factorial = 1;
    for (int i = 1; i <= n; ++i)
    {
        factorial *= i;
    }

    CHECK_EXPRESSION(factorial > 0);
    return factorial;
}