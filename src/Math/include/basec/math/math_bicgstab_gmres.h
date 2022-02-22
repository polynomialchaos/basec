/*******************************************************************************
 * @file math_bicgstab_gmres.h
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#ifndef MATH_BICGSTAB_GMRES_H
#define MATH_BICGSTAB_GMRES_H

#include <stdlib.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/** Math matrix vector multiplication function type */
typedef int (*math_int_ft)(double *p, double *v, size_t n, size_t m);

/*******************************************************************************
 * @brief Get the bicgstab n m work size
 * @param[in] n
 * @param[in] m
 * @return size_t
 ******************************************************************************/
size_t get_bicgstab_n_m_work_size(size_t n, size_t m);

/*******************************************************************************
 * @brief Get the gmres n m work size
 * @param[in] n
 * @param[in] m
 * @param[in] n_dims
 * @return size_t
 ******************************************************************************/
size_t get_gmres_n_m_work_size(size_t n, size_t m, int n_dims);

/*******************************************************************************
 * @brief Solve the system with the BiCGStab method
 * @param[in] n
 * @param[in] m
 * @param[in] b
 * @param[inout] x
 * @param[in] work
 * @param[in] matvec
 * @param[inout] iter
 * @param[inout] residual
 ******************************************************************************/
void solve_bicgstab_n_m(size_t n, size_t m, double *b, double *x, double *work,
                        math_int_ft matvec, int *iter, double *residual);

/*******************************************************************************
 * @brief Solve the system with the GMRes method
 * @param[in] n
 * @param[in] m
 * @param[in] b
 * @param[inout] x
 * @param[in] work
 * @param[in] matvec
 * @param[inout] iter
 * @param[inout] residual
 * @param[in] n_dims
 * @param[in] n_krylov_restarts
 ******************************************************************************/
void solve_gmres_n_m(size_t n, size_t m, double *b, double *x, double *work,
                     math_int_ft matvec, int *iter, double *residual,
                     int n_dims, int n_krylov_restarts);

#endif /* MATH_BICGSTAB_GMRES_H */