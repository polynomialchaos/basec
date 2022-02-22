/*******************************************************************************
 * @file basec_macro.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef BASEC_MACRO_H
#define BASEC_MACRO_H

/*******************************************************************************
 * @brief A macro to return absoute value
 ******************************************************************************/
#define ABS(a) (                \
    {                           \
        __typeof__(a) _a = (a); \
        _a < 0 ? -_a : _a;      \
    })

/*******************************************************************************
 * @brief A macro to compare values within epsilon tolerance
 ******************************************************************************/
#define EQ(a, b) (                                       \
    { ABS((a) - (b)) <= (BDEP * MAX(ABS((a)), ABS((b)))) \
          ? 1                                            \
          : 0; })

/*******************************************************************************
 * @brief A macro to compare value within epsilon tolerance to zero
 ******************************************************************************/
#define EQ0(a) ({ ABS((a)) <= (BDMN * 10) ? 1 : 0; })

/*******************************************************************************
 * @brief  A macro to return the maximum of two values
 ******************************************************************************/
#define MAX(a, b) (             \
    {                           \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

/*******************************************************************************
 * @brief  A macro to return the minimum of two values
 ******************************************************************************/
#define MIN(a, b) (             \
    {                           \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a < _b ? _a : _b;      \
    })

/*******************************************************************************
 * @brief A macro to return value as refernce
 ******************************************************************************/
#define REF(reference) &(reference)

/*******************************************************************************
 * @brief A macro to touch a pointer to prevent debug warnings
 ******************************************************************************/
#define UNUSED(pointer) (void)(pointer)

/*******************************************************************************
 * @brief A macro to return value as void refernce
 ******************************************************************************/
#define VOID_REF(pointer) (void *)REF(pointer)

/*******************************************************************************
 * @brief A macro to return a value from void reference
 ******************************************************************************/
#define VOID_DEREF(type, pointer) *(type *)pointer

#endif /* BASEC_MACRO_H */