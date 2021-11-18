/*******************************************************************************
 * @file math_bicgstab.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
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

    tmp += nm; // r
    tmp += nm; // rtld
    tmp += nm; // p
    tmp += nm; // v
    tmp += nm; // s
    tmp += nm; // t
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
    check_expression(matvec != NULL);
    size_t nm = n * m;
    size_t tmp = 0;

    double *r = &work[tmp];
    tmp += nm; // r
    double *rtld = &work[tmp];
    tmp += nm; // rtld
    double *p = &work[tmp];
    tmp += nm; // p
    double *v = &work[tmp];
    tmp += nm; // v
    double *s = &work[tmp];
    tmp += nm; // s
    double *t = &work[tmp];

    int max_iter = *iter;
    double tolerance = *residual;

    double rho = 1.0;
    double alpha = 1.0;
    double omega = 1.0;

    // Set initial residual
    copy_n(b, r, nm);
    copy_n(r, rtld, nm);

    set_value_n(0.0, p, nm);
    set_value_n(0.0, v, nm);
    set_value_n(0.0, s, nm);
    set_value_n(0.0, t, nm);
    set_value_n(0.0, x, nm);

    // Perform BiConjugate Gradient Stabilized iteration.
    for (*iter = 1; *iter <= max_iter; (*iter)++)
    {
        double rho_old = rho;
        rho = dot_n(rtld, r, nm);
        double beta = rho / rho_old * alpha / omega;

        // Compute vector P
        for (size_t i = 0; i < nm; ++i)
            p[i] = r[i] + beta * (p[i] - omega * v[i]);

        // Compute direction adjusting vector PHAT and scalar ALPHA.
        check_expression((*matvec)(p, v, n, m) == 0);

        alpha = rho / dot_n(rtld, v, nm);

        // Compute vector S.
        for (size_t i = 0; i < nm; ++i)
            s[i] = r[i] - alpha * v[i];

        // Compute stabilizer vector SHAT and scalar OMEGA.
        check_expression((*matvec)(s, t, n, m) == 0);

        omega = dot_n(t, s, nm) / dot_n(t, t, nm);

        // Compute new solution approximation vector X.
        for (size_t i = 0; i < nm; ++i)
            x[i] += alpha * p[i] + omega * s[i];

        // Compute residual R, check for tolerance
        for (size_t i = 0; i < nm; ++i)
            r[i] = s[i] - omega * t[i];

        *residual = len_n(r, nm);
        if (*residual <= tolerance)
            return;
    }

    log_error(MITF, __FUNCTION__, iter);
}