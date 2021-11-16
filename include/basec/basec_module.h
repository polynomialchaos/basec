/*******************************************************************************
 * @file basec_module.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-15
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef BASEC_MODULE_H
#define BASEC_MODULE_H

#define NULL_CHAR '\0' /** Null character */

/** File, line and function macro */
#define __PASS__ __FILE__, __LINE__, __FUNCTION__

#include "basec/basec_macro.h"
#include "basec/basec_type.h"

#include "basec/basec_print.h"
#include "basec/basec_logging.h"
#include "basec/basec_file.h"
#include "basec/basec_memory.h"
#include "basec/basec_string.h"
#include "basec/basec_string_conversion.h"
#include "basec/basec_time.h"

#endif /* BASEC_MODULE_H */