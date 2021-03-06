/*******************************************************************************
 * @file basec_type.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef BASEC_TYPE_H
#define BASEC_TYPE_H

#define BC_DMIN 1.e-200 /** Double minimum */
#define BC_DMAX 1.e200  /** Double maximum */
#define BC_DEPS 1.e-16  /** Double epsilon */

#define BC_NLCH '\0' /** Null character */

/** File, line and function macro */
#define __PASS__ __FILE__, __LINE__, __FUNCTION__

#define BC_TRUE 1   /** Boolean type True value */
#define BC_FALSE 0  /** Boolean type False value */
typedef int bool_t; /** Bool type */

typedef char *string_t;        /** String type */
typedef const char *cstring_t; /** Constant string type */

#endif /* BASEC_TYPE_H */