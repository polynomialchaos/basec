/*******************************************************************************
 * @file error.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <stdlib.h>
#include <stdarg.h>
#include "utils_private.h"

#define ULMS '=' /** Logging message separator symbol */

/** Logging level strings */
cstring_t level_strings[_logging_level_max] = {
    "DEBUG", "INFO", "WARNING", "ERROR"};

bool_t error_state = BC_FALSE;        /** Error state flag */
bool_t global_error_state = BC_FALSE; /** Global error state flag */
bool_t abort_active = BC_FALSE;       /** Abort active flag */
bool_t exit_with_failure = BC_TRUE;   /** Exit with failure flag */

/** Global error state function pointer */
void_ft global_error_state_handler_fun_ptr = NULL;

/** Error state function pointer */
void_ft error_state_handler_fun_ptr = NULL;

/** Exit function pointer */
void_ft exit_handler_fun_ptr = default_exit_handler;

/*******************************************************************************
 * @brief Set error and pass file, line, function and optional forwarded
 * file, line and function with format specifier as in printf
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] _file2
 * @param[in] _line2
 * @param[in] _function2
 * @param[in] level
 * @param[in] format
 * @param[in] ...
 ******************************************************************************/
void add_logging(cstring_t _file, int _line, cstring_t _function,
                 cstring_t _file2, int _line2, cstring_t _function2,
                 logging_level_t level, cstring_t format, ...)
{
    if (level > Warning)
        error_state = BC_TRUE;

    va_list arg;
    va_start(arg, format);

    if (level > Info)
    {
        BM_PRINT("\n");
        printf_r_sep(ULMS);
    }

    BM_PRINT("%s:", level_strings[level]);
    BM_VPRINT(format, arg);
    BM_PRINT("\n");

    if (_file)
        BM_PRINT("%s:%i:%s\n", _file, _line, _function);

    if (_file2)
        BM_PRINT("%s:%i:%s\n", _file2, _line2, _function2);

    if (level > Info)
    {
        printf_r_sep(ULMS);
    }

    va_end(arg);

    check_abort(BC_FALSE);
}

/*******************************************************************************
 * @brief Check for error state or final call and abort
 ******************************************************************************/
void check_abort(bool_t is_final)
{
    if (global_error_state_handler_fun_ptr != NULL)
        global_error_state_handler_fun_ptr();

    if (abort_active)
        return;

    if (!is_active_error() && !is_final)
        return;

    abort_active = 1;
    if (error_state_handler_fun_ptr)
        error_state_handler_fun_ptr();

    if (exit_handler_fun_ptr)
        exit_handler_fun_ptr();
}

/*******************************************************************************
 * @brief Default exit handler
 ******************************************************************************/
void default_exit_handler()
{
    if (is_active_error())
    {
        BM_PRINT("Failure exit!\n");
        exit(exit_with_failure ? EXIT_FAILURE : EXIT_SUCCESS);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

/*******************************************************************************
 * @brief Return error flag
 ******************************************************************************/
bool_t is_active_error()
{
    return (error_state || global_error_state);
}

/*******************************************************************************
 * @brief Set the error state handler
 * @param[in] fun_ptr
 ******************************************************************************/
void set_error_state_handler(void_ft fun_ptr)
{
    error_state_handler_fun_ptr = fun_ptr;
}

/*******************************************************************************
 * @brief Set the exit with failure flag
 * @param[in] do_failure
 ******************************************************************************/
void set_exit_with_failure(bool_t do_failure)
{
    exit_with_failure = do_failure;
}

/*******************************************************************************
 * @brief Set the global error
 * @param[in] error
 ******************************************************************************/
void set_global_error(bool_t error)
{
    global_error_state = error;
}

/*******************************************************************************
 * @brief Set the global error state handler
 * @param[in] fun_ptr
 ******************************************************************************/
void set_global_error_state_handler(void_ft fun_ptr)
{
    global_error_state_handler_fun_ptr = fun_ptr;
}

/*******************************************************************************
 * @brief Set the exit handler
 * @param[in] fun_ptr
 ******************************************************************************/
void set_exit_handler(void_ft fun_ptr)
{
    exit_handler_fun_ptr = fun_ptr;
}
