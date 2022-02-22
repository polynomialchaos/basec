################################################################################
# @file numerics.py
# @author Florian Eigentler
# @brief
# @version 1.0.0
# @date 2022-02-22
# @copyright Copyright (c) 2022 by Florian Eigentler.
#  This work is licensed under terms of the MIT license (<LICENSE>).
################################################################################
import numpy as np


def gaussSeidel(A, b, tolerance=1e-6, maxIter=100):
    """Solve the linear system of equations using Gauss algorithm."""
    b_mod = np.atleast_2d(b).T
    if A.shape[0] != b_mod.shape[0]:
        raise ValueError('Matrix and vector shape not valid!')

    # define the solution vector
    n, x_old, x = A.shape[0], np.zeros(b_mod.shape), np.zeros(b_mod.shape)

    for iter in range(maxIter):
        error = 0.0
        for k in range(n):
            s = np.zeros(b_mod.shape[1])
            for i in range(0, k):
                s += A[k, i] * x[i, :]
            for i in range(k+1, n):
                s += A[k, i] * x_old[i, :]

            x[k, :] = (b_mod[k, :] - s) / A[k, k]
            error = max(error, np.max(np.abs(x[k, :] - x_old[k, :])))

        if error < tolerance:
            print(iter, error)
            return x

        x_old = np.copy(x)

    raise ValueError('Gauss-Seidel did not converge!')


def BiCGStab(A, b, tolerance=1e-30, maxIter=100):
    """Solve the linear system of equations using BiCGStab algorithm."""
    b_mod = np.atleast_2d(b).T
    if A.shape[0] != b_mod.shape[0]:
        raise ValueError('Matrix and vector shape not valid!')

    x = np.zeros(b_mod.shape)
    r = b_mod - np.matmul(A, x)
    rs = r

    rho, alpha, omega = 1.0, 1.0, 1.0
    v, p = 0.0, 0.0

    norm_r = np.sqrt([np.dot(xx, yy) for xx, yy in zip(r.T, r.T)])
    norm_b = np.sqrt([np.dot(xx, yy) for xx, yy in zip(b_mod.T, b_mod.T)])

    for iter in range(maxIter):
        rho_prev = rho
        rho = np.array([np.dot(xx, yy) for xx, yy in zip(rs.T, r.T)])

        beta = (rho/rho_prev) * (alpha/omega)
        p = r + beta * (p-omega*v)
        v = np.matmul(A, p)
        alpha = rho/np.array([np.dot(xx, yy) for xx, yy in zip(rs.T, v.T)])

        s = r - alpha*v
        t = np.matmul(A, s)

        omega = np.array([np.dot(xx, yy) for xx, yy in zip(t.T, s.T)]) / \
            np.array([np.dot(xx, yy) for xx, yy in zip(t.T, t.T)])
        x = x + alpha*p + omega*s
        r = s - omega * t

        norm_r = np.sqrt([np.dot(xx, yy) for xx, yy in zip(r.T, r.T)])

        if (norm_r < tolerance*norm_b).all():
            print(iter, norm_r)
            return x

    raise ValueError('BiCGStab did not converge!')


################################################################################
# CALL BY SCRIPT
# ------------------------------------------------------------------------------
if __name__ == '__main__':

    M = np.array([[1, 2, 3], [4, 25, 6], [1, 8, 1]])
    b = np.array([1.083, 2, 1.25])

    print(gaussSeidel(M, b))
    print(BiCGStab(M, b))
    print(np.linalg.solve(M, b))
