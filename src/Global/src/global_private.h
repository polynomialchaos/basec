/*******************************************************************************
 * @file global_private.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef GLOBAL_PRIVATE_H
#define GLOBAL_PRIVATE_H

#include "basec/global_module.h"

#define GBMS '=' /** Message separator symbol */

/*******************************************************************************
 * @brief Call the list of initialize functions
 ******************************************************************************/
void call_initialize_list();

/*******************************************************************************
 * @brief Call the list of finalize functions
 ******************************************************************************/
void call_finalize_list();

#endif /* GLOBAL_PRIVATE_H */