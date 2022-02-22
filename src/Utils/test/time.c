/*******************************************************************************
 * @file time.c
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
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    double clock_time = 0.0;

    string_t date = GET_DATE_STRING_NOW();
    string_t time = GET_TIME_STRING_NOW();
    string_t datetime = GET_DATE_TIME_STRING_NOW();

    clock_time = get_clock_time(clock_time);
    string_t clock_time_string = get_clock_time_string(clock_time);

    PRINTF("%s ... %s ... %s ... %s\n",
           date, time, datetime, clock_time_string);

    DEALLOCATE(date);
    DEALLOCATE(time);
    DEALLOCATE(datetime);
    DEALLOCATE(clock_time_string);

    return 0;
}