/*******************************************************************************
 * @file logging.c
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
 * @brief Global error state handler
 * @return int
 ******************************************************************************/
void global_error_state_handler()
{
    BM_PRINT("Calling global error state handler (%d)!\n", is_active_error());
    return;
}

/*******************************************************************************
 * @brief Error state handler
 * @return int
 ******************************************************************************/
void error_state_handler()
{
    BM_PRINT("Calling error state handler (%d)!\n", is_active_error());
    return;
}

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    set_global_error_state_handler(global_error_state_handler);
    set_error_state_handler(error_state_handler);

    BM_LOG_DEBUG("Logging debug message!");
    BM_LOG_INFO("Logging info message!");
    LOG_WARNING("Logging warning message!");

    set_exit_with_failure(BC_FALSE);
    BM_LOG_ERROR("Logging error message!");

    return 0;
}