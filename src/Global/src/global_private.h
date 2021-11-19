/*******************************************************************************
 * @file global_private.h
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
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