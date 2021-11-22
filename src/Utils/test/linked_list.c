/*******************************************************************************
 * @file time.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Deallocate data
 * @return int
 ******************************************************************************/
void deallocate_data(void *data)
{
    PRINTF("deallcoate: %d\n", VOID_DEREF(int, data));
    return;
}

/*******************************************************************************
 * @brief Check function
 * @return int
 ******************************************************************************/
bool_t check_data(void *data)
{
    int tmp = VOID_DEREF(int, data);
    PRINTF("check: %d\n", tmp == -10 ? BTRU : BFLS);
    return tmp == -10 ? BTRU : BFLS;
}

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    list_t *test = LIST_ALLOCATE(deallocate_data);

    CHECK_EXPRESSION(list_length(test) == 0);

    int test_val = 0;
    LIST_APPEND(test, sizeof(test_val), REF(test_val));

    test_val = -5;
    LIST_APPEND(test, sizeof(test_val), REF(test_val));

    test_val = -10;
    LIST_PREPEND(test, sizeof(test_val), REF(test_val));
    CHECK_EXPRESSION(list_length(test) == 3);

    CHECK_EXPRESSION(LIST_ALL(test, check_data) == BFLS);
    CHECK_EXPRESSION(LIST_ANY(test, check_data) == BTRU);

    LIST_FOR_EACH(test, deallocate_data);

    CHECK_EXPRESSION(VOID_DEREF(int, LIST_GET_FIRST(test)) == -10);
    CHECK_EXPRESSION(VOID_DEREF(int, LIST_GET_ITH(test, 1)) == 0);
    CHECK_EXPRESSION(VOID_DEREF(int, LIST_GET_LAST(test)) == -5);

    LIST_DEALLOCATE_ITH(test, 0);
    LIST_DEALLOCATE_ITH(test, 0);
    CHECK_EXPRESSION(list_length(test) == 1);

    LIST_DEALLOCATE(test);
    DEALLOCATE(test);

    return 0;
}
