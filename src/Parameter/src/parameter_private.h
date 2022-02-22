/*******************************************************************************
 * @file parameter_private.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef PARAMETER_PRIVATE_H
#define PARAMETER_PRIVATE_H

#include "basec/json_module.h"
#include "basec/parameter_module.h"

#define PVLK "value" /** Parameter value string */

extern JSON_t *user_defaults; /** Static field for user defaults */
extern JSON_t *user_inputs;   /** Static field for user inputs */

extern int as_json_type[]; /** Parameter type sizes */

/*******************************************************************************
 * @brief Get the parameter object by path
 * @param[in] _file
 * @param[in] _line
 * @param[in] _function
 * @param[in] path
 * @param[in] is_required
 * @return JSON_t*
 ******************************************************************************/
JSON_t *get_parameter_path_pass(cstring_t _file, int _line, cstring_t _function,
                                cstring_t path, int is_required);

#endif /* PARAMETER_PRIVATE_H */