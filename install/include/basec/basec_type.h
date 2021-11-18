/*******************************************************************************
 * @file basec_type.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2021-11-15
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef BASEC_TYPE_H
#define BASEC_TYPE_H

#define BDMN 1.e-200 /** Double minimum */
#define BDMX 1.e200  /** Double maximum */
#define BDEP 1.e-16  /** Double epsilon */

#define BNCH '\0' /** Null character */

/** File, line and function macro */
#define __PASS__ __FILE__, __LINE__, __FUNCTION__

#define BTRU 1      /** Boolean type True value */
#define BFLS 0      /** Boolean type False value */
typedef int bool_t; /** Bool type */

typedef char *string_t;        /** String type */
typedef const char *cstring_t; /** Constant string type */

#endif /* BASEC_TYPE_H */