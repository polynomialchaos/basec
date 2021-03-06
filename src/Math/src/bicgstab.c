/*******************************************************************************
 * @file math_bicgstab.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include "basec/utils_module.h"
#include "math_private.h"

/*******************************************************************************
 * @brief Get the bicgstab n m work size
 * @param[in] n
 * @param[in] m
 * @return size_t
 ******************************************************************************/
size_t get_bicgstab_n_m_work_size(size_t n, size_t m)
{
    size_t nm = n * m;
    size_t tmp = 0;

    tmp += nm; /** r */
    tmp += nm; /** rtld */
    tmp += nm; /** p */
    tmp += nm; /** v */
    tmp += nm; /** s */
    tmp += nm; /** t */
    return tmp;
}

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
                        math_int_ft matvec, int *iter, double *residual)
{
    BM_CHECK_EXPRESSION(matvec != NULL);
    size_t nm = n * m;
    size_t tmp = 0;

    double *r = &work[tmp];
    tmp += nm; /** r */
    double *rtld = &work[tmp];
    tmp += nm; /** rtld */
    double *p = &work[tmp];
    tmp += nm; /** p */
    double *v = &work[tmp];
    tmp += nm; /** v */
    double *s = &work[tmp];
    tmp += nm; /** s */
    double *t = &work[tmp];

    int max_iter = *iter;
    double tolerance = *residual;

    double rho = 1.0;
    double alpha = 1.0;
    double omega = 1.0;

    /** Set initial residual */
    copy_n(b, nm, r);
    copy_n(r, nm, rtld);

    set_value_n(0.0, nm, p);
    set_value_n(0.0, nm, v);
    set_value_n(0.0, nm, s);
    set_value_n(0.0, nm, t);
    set_value_n(0.0, nm, x);

    /** Perform BiConjugate Gradient Stabilized iteration. */
    for (*iter = 1; *iter <= max_iter; (*iter)++)
    {
        double rho_old = rho;
        rho = dot_n(rtld, r, nm);
        double beta = rho / rho_old * alpha / omega;

        /** Compute vector P */
        for (size_t i = 0; i < nm; ++i)
            p[i] = r[i] + beta * (p[i] - omega * v[i]);

        /** Compute direction adjusting vector PHAT and scalar ALPHA. */
        BM_CHECK_EXPRESSION((*matvec)(p, v, n, m) == 0);

        alpha = rho / dot_n(rtld, v, nm);

        /** Compute vector S. */
        for (size_t i = 0; i < nm; ++i)
            s[i] = r[i] - alpha * v[i];

        /** Compute stabilizer vector SHAT and scalar OMEGA. */
        BM_CHECK_EXPRESSION((*matvec)(s, t, n, m) == 0);

        omega = dot_n(t, s, nm) / dot_n(t, t, nm);

        /** Compute new solution approximation vector X. */
        for (size_t i = 0; i < nm; ++i)
            x[i] += alpha * p[i] + omega * s[i];

        /** Compute residual R, check for tolerance */
        for (size_t i = 0; i < nm; ++i)
            r[i] = s[i] - omega * t[i];

        *residual = len_n(r, nm);
        if (*residual <= tolerance)
            return;
    }

    BM_LOG_ERROR(MITF, __FUNCTION__, iter);
}