/*******************************************************************************
 * @file bicgstab_gmres.c
 * @author Florian Eigentler
 * @brief
 * @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
 ******************************************************************************/
#include <math.h>
#include "basec/utils_module.h"
#include "basec/math_module.h"

/*******************************************************************************
 * @brief Matrix vector multiplication
 * @return int
 ******************************************************************************/
int matrix_vector_n_m(double *p, double *v, size_t n, size_t m)
{
#if DEBUG
    BM_UNUSED(m);
#endif /* DEBUG */

    double a[] = {1, 2, 3, 4, 25, 6, 1, 8, 1};
    for (size_t i = 0; i < n; ++i)
    {
        double *aa = &a[i * n];

        v[i] = 0;
        for (int j = 0; j < 3; ++j)
        {
            v[i] += aa[j] * p[j];
        }
    }

    return 0;
}

/*******************************************************************************
 * @brief Main function
 * @return int
 ******************************************************************************/
int main()
{
    int n = 3;
    int iter = 100;
    double residual = 1e-32;

    double b[] = {1.083, 2, 1.25};
    double x[3];

    double *work = BM_ALLOCATE(sizeof(double) * get_bicgstab_n_m_work_size(n, 1));

    iter = 100;
    residual = 1e-32;
    solve_bicgstab_n_m(n, 1, b, x, work, matrix_vector_n_m, &iter, &residual);
    BM_PRINT("%d / %e: %e %e %e\n", iter, residual, x[0], x[1], x[2]);

    BM_DEALLOCATE(work);

    work = BM_ALLOCATE(sizeof(double) * get_gmres_n_m_work_size(n, 1, 20));

    iter = 100;
    residual = 1e-32;
    solve_gmres_n_m(n, 1, b, x, work,
                    matrix_vector_n_m, &iter, &residual, 20, 10);
    BM_PRINT("%d / %e: %e %e %e\n", iter, residual, x[0], x[1], x[2]);

    BM_DEALLOCATE(work);

    return 0;
}