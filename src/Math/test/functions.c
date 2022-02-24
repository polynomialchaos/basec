/*******************************************************************************
 * @file functions.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <math.h>
#include "basec/utils_module.h"
#include "basec/math_module.h"

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    BM_CHECK_EXPRESSION(BM_EQ(factorial(0), 1));
    BM_CHECK_EXPRESSION(BM_EQ(factorial(1), 1));
    BM_CHECK_EXPRESSION(BM_EQ(factorial(2), 2));
    BM_CHECK_EXPRESSION(BM_EQ(factorial(3), 6));

    return 0;
}