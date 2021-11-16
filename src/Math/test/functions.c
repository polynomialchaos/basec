/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include "basec/utils_module.h"
#include "basec/math_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    check_expression(EQ_T(factorial(0), 1));
    check_expression(EQ_T(factorial(1), 1));
    check_expression(EQ_T(factorial(2), 2));
    check_expression(EQ_T(factorial(3), 6));

    return 0;
}