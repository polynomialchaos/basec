/*******************************************************************************
 * @file version.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "utils_private.h"

/*******************************************************************************
 * @brief Get the version string
 * @return string_t
 ******************************************************************************/
string_t get_version_string()
{
    return VERSION;
}