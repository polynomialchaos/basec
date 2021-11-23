/*******************************************************************************
 * @file logging.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/utils_module.h"

/*******************************************************************************
 * @brief Global error state handler
 * @return int
 ******************************************************************************/
void global_error_state_handler()
{
    PRINTF("Calling global error state handler (%d)!\n", is_active_error());
    return;
}

/*******************************************************************************
 * @brief Error state handler
 * @return int
 ******************************************************************************/
void error_state_handler()
{
    PRINTF("Calling error state handler (%d)!\n", is_active_error());
    return;
}

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    set_global_error_state_handler(global_error_state_handler);
    set_error_state_handler(error_state_handler);

    LOG_DEBUG("Logging debug message!");
    LOG_INFO("Logging info message!");
    LOG_WARNING("Logging warning message!");

    set_exit_with_failure(BFLS);
    LOG_ERROR("Logging error message!");

    return 0;
}