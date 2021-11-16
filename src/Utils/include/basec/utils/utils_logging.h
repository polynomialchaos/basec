/*******************************************************************************
 * @file utils_logging.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-07
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef UTILS_LOGGING_H
#define UTILS_LOGGING_H

#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief A macro to add a debug message and pass file, line and function
 ******************************************************************************/
#define log_debug_pass(_file, _line, _function, format, ...) \
    add_logging(__PASS__, (_file), (_line), (_function),     \
                (Debug), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add a debug message
 ******************************************************************************/
#define log_debug(format, ...) \
    log_debug_pass((NULL), (0), (NULL), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add an error and pass file, line and function
 ******************************************************************************/
#define log_error_pass(_file, _line, _function, format, ...) \
    add_logging(__PASS__, (_file), (_line), (_function),     \
                (Error), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add an error
 ******************************************************************************/
#define log_error(format, ...) \
    log_error_pass((NULL), (0), (NULL), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add a info message and pass file, line and function
 ******************************************************************************/
#define log_info_pass(_file, _line, _function, format, ...) \
    add_logging(__PASS__, (_file), (_line), (_function),    \
                (Info), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add a info message
 ******************************************************************************/
#define log_info(format, ...) \
    log_info_pass((NULL), (0), (NULL), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add a warning and pass file, line and function
 ******************************************************************************/
#define log_warning_pass(_file, _line, _function, format, ...) \
    add_logging(__PASS__, (_file), (_line), (_function),       \
                (Warning), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to add a warning
 ******************************************************************************/
#define log_warning(format, ...) \
    log_warning_pass((NULL), (0), (NULL), (format), ##__VA_ARGS__)

/*******************************************************************************
 * @brief A macro to check an expression and pass file, line and function
 ******************************************************************************/
#define check_expression_pass(_file, _line, _function, expression)        \
    (                                                                     \
        {                                                                 \
            if (!(expression))                                            \
                log_error_pass((_file), (_line), (_function),             \
                               "Expression '%s' failed!", (#expression)); \
        })

/*******************************************************************************
 * @brief A macro to check an expression
 ******************************************************************************/
#define check_expression(expression) \
    check_expression_pass((NULL), (0), (NULL), (expression))

/*******************************************************************************
 * @brief A macro to restore default abort handler
 ******************************************************************************/
#define reset_error_state_handler() set_error_state_handler(NULL)

/*******************************************************************************
 * @brief A macro to restore global error handler
 ******************************************************************************/
#define reset_global_error_state_handler() set_global_error_state_handler(NULL)

typedef void (*void_ft)(); /** Abort handler function type */

/*******************************************************************************
 * @brief Logging level enumeration
 ******************************************************************************/
typedef enum LoggingLevel
{
    Debug,   /** Debug logging level */
    Info,    /** Info logging level */
    Warning, /** Warning logging level */
    Error,   /** Error logging level */
    _logging_level_max
} logging_level_t;

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
                 logging_level_t level, cstring_t format, ...);

/*******************************************************************************
 * @brief Check for error state or final call and abort
 ******************************************************************************/
void check_abort(bool_t is_final);

/*******************************************************************************
 * @brief Return error flag
 ******************************************************************************/
bool_t is_active_error();

/*******************************************************************************
 * @brief Set the error state handler
 * @param fun_ptr
 ******************************************************************************/
void set_error_state_handler(void_ft fun_ptr);

/*******************************************************************************
 * @brief Set the exit with failure flag
 * @param do_failure
 ******************************************************************************/
void set_exit_with_failure(bool_t do_failure);

/*******************************************************************************
 * @brief Set the global error
 * @param error
 ******************************************************************************/
void set_global_error(bool_t error);

/*******************************************************************************
 * @brief Set the global error state handler
 * @param fun_ptr
 ******************************************************************************/
void set_global_error_state_handler(void_ft fun_ptr);

/*******************************************************************************
 * @brief Set the exit handler
 * @param fun_ptr
 ******************************************************************************/
void set_exit_handler(void_ft fun_ptr);

#endif /* UTILS_LOGGING_H */