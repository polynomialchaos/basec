/*******************************************************************************
 * @file base_time.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef UTILS_TIME_H
#define UTILS_TIME_H

#include <time.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro that generates a date string based on current time.
 ******************************************************************************/
#define BM_GET_DATE_STRING_NOW() get_date_string(get_now())

/*******************************************************************************
 * @brief A macro that generates a date/time string based on current time.
 ******************************************************************************/
#define BM_GET_DATE_TIME_STRING_NOW() get_date_time_string(get_now())

/*******************************************************************************
 * @brief A macro that generates a time string based on current time.
 ******************************************************************************/
#define BM_GET_TIME_STRING_NOW() get_time_string(get_now())

/*******************************************************************************
 * @brief Get the clock time
 * @param[in] initial
 * @return double
 ******************************************************************************/
double get_clock_time(double initial);

/*******************************************************************************
 * @brief Get the clock time string
 * @param[in] clock_time
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
 * @param[in] time
 * @return string_t
 ******************************************************************************/
string_t get_time_string(time_t time);

#endif /* UTILS_TIME_H */