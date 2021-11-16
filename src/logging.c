/*******************************************************************************
 * @file error.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <stdlib.h>
#include <stdarg.h>
#include "logging_private.h"

#define MSG_SYM '=' /** Logging message separator symbol */

/** Logging level strings */
cstring_t level_strings[_logging_level_max] = {
    "DEBUG", "INFO", "WARNING", "ERROR"};

bool_t error_state = FALSE;        /** Error state flag */
bool_t global_error_state = FALSE; /** Global error state flag */
bool_t abort_active = FALSE;       /** Abort active flag */
bool_t exit_with_failure = TRUE;   /** Exit with failure flag */

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
 * @param ...
 ******************************************************************************/
void add_logging(cstring_t _file, int _line, cstring_t _function,
                 cstring_t _file2, int _line2, cstring_t _function2,
                 logging_level_t level, cstring_t format, ...)
{
    if (level > Warning)
        error_state = TRUE;

    va_list arg;
    va_start(arg, format);

    if (level > Info)
    {
        printf_r("\n");
        printf_r_sep(MSG_SYM);
    }

    printf_r("%s:", level_strings[level]);
    vprintf_r(format, arg);
    printf_r("\n");

    if (_file)
        printf_r("%s:%i:%s\n", _file, _line, _function);

    if (_file2)
        printf_r("%s:%i:%s\n", _file2, _line2, _function2);

    if (level > Info)
    {
        printf_r_sep(MSG_SYM);
    }

    va_end(arg);

    check_abort(FALSE);
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
        printf_r("Failure exit!\n");
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
 * @brief Set the exit with failure flag
 * @param do_failure
 ******************************************************************************/
void set_exit_with_failure(bool_t do_failure)
{
    exit_with_failure = do_failure;
}

/*******************************************************************************
 * @brief Set the global error
 * @param error
 ******************************************************************************/
void set_global_error(bool_t error)
{
    global_error_state = error;
}

/*******************************************************************************
 * @brief Set the global error state handler
 * @param fun_ptr
 ******************************************************************************/
void set_global_error_state_handler(void_ft fun_ptr)
{
    global_error_state_handler_fun_ptr = fun_ptr;
}

/*******************************************************************************
 * @brief Set the exit handler
 * @param fun_ptr
 ******************************************************************************/
void set_exit_handler(void_ft fun_ptr)
{
    exit_handler_fun_ptr = fun_ptr;
}
