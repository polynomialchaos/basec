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
 * @brief Main test function
 * @return int
 ******************************************************************************/
int main()
{
    double clock_time = 0.0;

    string_t date = get_date_string_now();
    string_t time = get_time_string_now();
    string_t datetime = get_date_time_string_now();

    clock_time = get_clock_time(clock_time);
    string_t clock_time_string = get_clock_time_string(clock_time);

    printf_r("%s ... %s ... %s ... %s\n",
             date, time, datetime, clock_time_string);

    DEALLOCATE(date);
    DEALLOCATE(time);
    DEALLOCATE(datetime);
    DEALLOCATE(clock_time_string);

    return 0;
}