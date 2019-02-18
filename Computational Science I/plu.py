# PLU Decomposition
# Input: n X n matrix A
# Output: n X n matrices L and U such that LU=A and L and U are triangular

import math
import scipy
import copy

def PLU(A):
    ok = 1
    small = 1e-12
    n = scipy.shape(A)[0]
    U = copy.copy(A)
    L = scipy.identity(n)
    P = scipy.identity(n)
    for j in range(1, n):
        s = scipy.argmax(abs(U[j-1:n,j-1])) + j - 1
        if s != j-1:
            U = swap(U, s, j-1, n)
            P = swap(P, s, j-1, n)
            if j > 1:
                L = swap(L, s, j-1, j-1)
        for i in range(j+1, n+1):
            if abs(U[j-1,j-1]) < small:
                print("Near-zero pivot!")
                ok = 0
                break
            L[i-1, j-1] = U[i-1, j-1] / U[j-1, j-1]
            for k in range(j, n+1):
                U[i-1, k-1] = U[i-1, k-1] - L[i-1, j-1] * U[j-1, j-1]
    return L, U, P, ok

def swap(M, i, j, k):
    dum = copy.copy(M[i, 0:k])
    M[i, 0:k] = copy.copy(M[j, 0:k])
    M[j, 0:k] = copy.copy(dum)
    return M

# Test Script
A = scipy.matrix([[0.2, 1.4, -0.4, 12.3], [-2.3, 4.2, 1.1, -0.9], [9.2, -2.3, -0.1, 2.2], [3.4, 3.3, -10.1, 4.0]])

L, U, P, ok = PLU(A)
print('Matrix is')
print(A)
if ok == 1:
    print("L is")
    print(L)
    print("U is")
    print(U)
    print("P is")
    print(P)