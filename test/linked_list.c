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
 * @brief Deallocate data
 * @return int
 ******************************************************************************/
void deallocate_data(void *data)
{
    printf_r("deallcoate: %d\n", VOID_DEREF(int, data));
    return;
}

/*******************************************************************************
 * @brief Check function
 * @return int
 ******************************************************************************/
bool_t check_data(void *data)
{
    int tmp = VOID_DEREF(int, data);
    printf_r("check: %d\n", tmp == -10 ? TRUE : FALSE);
    return tmp == -10 ? TRUE : FALSE;
}

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    list_t *test = list_allocate(deallocate_data);

    check_expression(list_length(test) == 0);

    int test_val = 0;
    list_append(test, sizeof(test_val), REF(test_val));

    test_val = -5;
    list_append(test, sizeof(test_val), REF(test_val));

    test_val = -10;
    list_prepend(test, sizeof(test_val), REF(test_val));
    check_expression(list_length(test) == 3);

    check_expression(list_all(test, check_data) == FALSE);
    check_expression(list_any(test, check_data) == TRUE);

    list_for_each(test, deallocate_data);

    check_expression(VOID_DEREF(int, list_get_first(test)) == -10);
    check_expression(VOID_DEREF(int, list_get_ith(test, 1)) == 0);
    check_expression(VOID_DEREF(int, list_get_last(test)) == -5);

    list_deallocate_ith(test, 0);
    list_deallocate_ith(test, 0);
    check_expression(list_length(test) == 1);

    list_deallocate(test);
    DEALLOCATE(test);

    return 0;
}
