/*******************************************************************************
 * @file linked_list.c
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
 * @brief Deallocate data
 * @return int
 ******************************************************************************/
void deallocate_data(void *data)
{
    BM_PRINT("deallcoate: %d\n", BM_VOID_DEREF(int, data));
    return;
}

/*******************************************************************************
 * @brief Check function
 * @return int
 ******************************************************************************/
bool_t check_data(void *data)
{
    int tmp = BM_VOID_DEREF(int, data);
    BM_PRINT("check: %d\n", tmp == -10 ? BC_TRUE : BC_FALSE);
    return tmp == -10 ? BC_TRUE : BC_FALSE;
}

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    list_t *test = BM_LIST_ALLOCATE(deallocate_data);

    BM_CHECK_EXPRESSION(list_length(test) == 0);

    int test_val = 0;
    BM_LIST_APPEND(test, sizeof(test_val), BM_REF(test_val));

    test_val = -5;
    BM_LIST_APPEND(test, sizeof(test_val), BM_REF(test_val));

    test_val = -10;
    BM_LIST_PREPEND(test, sizeof(test_val), BM_REF(test_val));
    BM_CHECK_EXPRESSION(list_length(test) == 3);

    BM_CHECK_EXPRESSION(BM_LIST_ALL(test, check_data) == BC_FALSE);
    BM_CHECK_EXPRESSION(BM_LIST_ANY(test, check_data) == BC_TRUE);

    BM_LIST_FOR_EACH(test, deallocate_data);

    BM_CHECK_EXPRESSION(BM_VOID_DEREF(int, BM_LIST_GET_FIRST(test)) == -10);
    BM_CHECK_EXPRESSION(BM_VOID_DEREF(int, BM_LIST_GET_ITH(test, 1)) == 0);
    BM_CHECK_EXPRESSION(BM_VOID_DEREF(int, BM_LIST_GET_LAST(test)) == -5);

    BM_LIST_DEALLOCATE_ITH(test, 0);
    BM_LIST_DEALLOCATE_ITH(test, 0);
    BM_CHECK_EXPRESSION(list_length(test) == 1);

    BM_LIST_DEALLOCATE(test);
    BM_DEALLOCATE(test);

    return 0;
}
