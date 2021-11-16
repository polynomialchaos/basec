/*******************************************************************************
 * @file base_time.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef BASE_TIME_H
#define BASE_TIME_H

#include <time.h>
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro that generates a date string based on current time.
 ******************************************************************************/
#define get_date_string_now() get_date_string(get_now())

/*******************************************************************************
 * @brief A macro that generates a date/time string based on current time.
 ******************************************************************************/
#define get_date_time_string_now() get_date_time_string(get_now())

/*******************************************************************************
 * @brief A macro that generates a time string based on current time.
 ******************************************************************************/
#define get_time_string_now() get_time_string(get_now())

/*******************************************************************************
 * @brief Get the clock time
 * @param[in] initial
 * @return double
 ******************************************************************************/
double get_clock_time(double initial);

/*******************************************************************************
 * @brief Get the clock time string
 * @param clock_time
 * @return string_t
 ******************************************************************************/
string_t get_clock_time_string(double clock_time);

/*******************************************************************************
 * @brief Get the date string based on given time.
 * @param[in] time
 * @return string_t
 ******************************************************************************/
string_t get_date_string(time_t time);

/*******************************************************************************
 * @brief Get the date time string based on given time.
 * @param[in] time
 * @return string_t
 ******************************************************************************/
string_t get_date_time_string(time_t time);

/*******************************************************************************
 * @brief Get the current time
 * @return time_t
 ******************************************************************************/
time_t get_now();

/*******************************************************************************
 * @brief Get the time string based on given time.
 * @param time
 * @return string_t
 ******************************************************************************/
string_t get_time_string(time_t time);

#endif /* BASE_TIME_H */