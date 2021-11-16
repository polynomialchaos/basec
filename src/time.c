/*******************************************************************************
 * @file time.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <string.h>
#include "basec/basec_module.h"

#define LEN_DATE 50                         /** Maximum date string length */
#define LEN_TIME LEN_DATE                   /** Maximum date string length */
#define LEN_DATE_TIME (LEN_DATE + LEN_TIME) /** Maximum date string length */

/*******************************************************************************
 * @brief Get the clock time
 * @param[in] initial
 * @return double
 ******************************************************************************/
double get_clock_time(double initial)
{
    clock_t tmp = clock();
    return (double)tmp / CLOCKS_PER_SEC - initial;
}

/*******************************************************************************
 * @brief Get the clock time string
 * @param clock_time
 * @return string_t
 ******************************************************************************/
string_t get_clock_time_string(double clock_time)
{
    char tmp[LEN_TIME];

    int h = (int)(clock_time / 3600.0);
    int m = (int)((clock_time - h * 3600.0) / 60.0);
    int s = (int)((clock_time - h * 3600.0 - m * 60.0));

    double ms = clock_time - (h * 60.0 + m * 3600.0 + s);
    snprintf(tmp, LEN_TIME - 1, "%dh:%dm:%ds,%e", h, m, s, ms);

    return allocate_strcpy(trim(tmp));
}

/*******************************************************************************
 * @brief Get the date string based on given time.
 * @param[in] time
 * @return string_t
 ******************************************************************************/
string_t get_date_string(time_t time)
{
    char tmp[LEN_DATE];
    strftime(tmp, LEN_DATE - 1, "%d-%m-%Y", localtime(&time));
    return allocate_strcpy(trim(tmp));
}

/*******************************************************************************
 * @brief Get the date time string based on given time.
 * @param[in] time
 * @return string_t
 ******************************************************************************/
string_t get_date_time_string(time_t time)
{
    char tmp[LEN_DATE_TIME];
    strftime(tmp, LEN_DATE_TIME - 1, "%d-%m-%YT%H:%M:%S", localtime(&time));
    return allocate_strcpy(trim(tmp));
}

/*******************************************************************************
 * @brief Get the current time
 * @return time_t
 ******************************************************************************/
time_t get_now()
{
    return time(NULL);
}

/*******************************************************************************
 * @brief Get the time string based on given time.
 * @param time
 * @return string_t
 ******************************************************************************/
string_t get_time_string(time_t time)
{
    char tmp[LEN_TIME];
    strftime(tmp, LEN_TIME - 1, "%H:%M:%S", localtime(&time));
    return allocate_strcpy(trim(tmp));
}
