/*******************************************************************************
 * @file main.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdio.h>
#include "basec/basec_module.h"

/*******************************************************************************
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    log_debug("Logging debug message!");
    log_info("Logging info message!");
    log_warning("Logging warning message!");

    set_exit_with_failure(FALSE);
    log_error("Logging error message!");

    return 0;
}