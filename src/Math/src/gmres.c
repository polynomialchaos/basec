/*******************************************************************************
 * @file math_gmres.c
 * @author Florian Eigentler
 * @brief
 * @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#include <math.h>
#include "bicgstab_gmres_private.h"

/*******************************************************************************
 * @brief Get the gmres n m work size
 * @param n
 * @param m
 * @param n_dims
 * @return size_t
 ******************************************************************************/
size_t get_gmres_n_m_work_size(size_t n, size_t m, int n_dims)
{
    size_t nm = n * m;
    size_t tmp = 0;

    tmp += n_dims;                      // c
    tmp += n_dims;                      // s
    tmp += n_dims;                      // y
    tmp += n_dims + 1;                  // gam
    tmp += (n_dims + 1) * (n_dims + 1); // h
    tmp += nm * n_dims;                 // v
    tmp += nm;                          // w
    tmp += nm;                          // r0

    return tmp;
}

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
                     int n_dims, int n_krylov_restarts)
{
    check_expression(matvec != NULL);
    size_t nm = n * m;
    size_t tmp = 0;

    double *c = &work[tmp];
    tmp += n_dims; // c
    double *s = &work[tmp];
    tmp += n_dims; // s
    double *y = &work[tmp];
    tmp += n_dims; // y
    double *gam = &work[tmp];
    tmp += n_dims + 1; // gam
    double *h = &work[tmp];
    tmp += (n_dims + 1) * (n_dims + 1); // h
    double *v = &work[tmp];
    tmp += nm * n_dims; // v
    double *w = &work[tmp];
    tmp += nm; // w
    double *r0 = &work[tmp];

    *iter = 0;
    double tolerance = *residual;

    set_value_n(0.0, x, nm);
    copy_n(b, r0, nm);

    double norm_r0 = len_n(b, nm);

    // Perform GMRes iteration
    for (int ikr = 0; ikr < n_krylov_restarts; ++ikr)
    {
        for (size_t i = 0; i < nm; ++i)
            v[i] = r0[i] / norm_r0;

        gam[0] = norm_r0;

        for (int j = 0; j < n_dims; ++j)
        {
            *iter += 1;

            check_expression((*matvec)(&v[j * nm], w, n, m) == 0);

            // Gram-Schmidt
            for (int i = 0; i <= j; ++i)
            {
                h[i * n_dims + j] = dot_n(&v[i * nm], w, nm);
                for (size_t k = 0; k < nm; ++k)
                    w[k] = w[k] - h[i * n_dims + j] * v[i * nm + k];
            }

            h[(j + 1) * n_dims + j] = len_n(w, nm);

            // Givens Rotation
            for (int i = 0; i <= j - 1; ++i)
            {
                double tmp = c[i] * h[i * n_dims + j] +
                             s[i] * h[(i + 1) * n_dims + j];

                h[(i + 1) * n_dims + j] = -s[i] * h[i * n_dims + j] +
                                          c[i] * h[(i + 1) * n_dims + j];

                h[i * n_dims + j] = tmp;
            }

            double beta = sqrt(h[j * n_dims + j] * h[j * n_dims + j] +
                               h[(j + 1) * n_dims + j] *
                                   h[(j + 1) * n_dims + j]);

            s[j] = h[(j + 1) * n_dims + j] / beta;
            c[j] = h[j * n_dims + j] / beta;
            h[j * n_dims + j] = beta;
            gam[j + 1] = -s[j] * gam[j];
            gam[j] = c[j] * gam[j];

            *residual = sqrt(ABS_T(gam[j + 1]));
            if ((*residual <= tolerance) || (j == n_dims - 1))
            {
                for (int i = j; i >= 0; --i)
                {
                    y[i] = gam[i];
                    for (int k = i + 1; k <= j; ++k)
                        y[i] -= h[i * n_dims + k] * y[k];

                    y[i] /= h[i * n_dims + i];
                }

                for (int i = 0; i <= j; ++i)
                {
                    for (size_t k = 0; k < nm; ++k)
                        x[k] += y[i] * v[i * nm + k];
                }

                if (*residual <= tolerance)
                    return;
            }
            else
            {
                for (size_t i = 0; i < nm; ++i)
                    v[(j + 1) * nm + i] = w[i] / h[(j + 1) * n_dims + j];
            }
        }

        check_expression((*matvec)(x, r0, n, m) == 0);
        for (size_t i = 0; i < nm; ++i)
            r0[i] = b[i] - r0[i];

        norm_r0 = len_n(r0, nm);
    }

    log_error(MATH_ITER_FMT, __FUNCTION__, iter);
}