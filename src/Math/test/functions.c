/*******************************************************************************
 * @file functions.c
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
    CHECK_EXPRESSION(EQ(factorial(0), 1));
    CHECK_EXPRESSION(EQ(factorial(1), 1));
    CHECK_EXPRESSION(EQ(factorial(2), 2));
    CHECK_EXPRESSION(EQ(factorial(3), 6));

    return 0;
}