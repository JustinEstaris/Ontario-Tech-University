# By L. van Veen, UOIT 2019.
# PLU decomposition (with pivoting)
# Input: n X n matrix A
# Output: n X n matrices L and U such that LU=PA and L and U are triangular
import math
import scipy
import copy

def PLU(A):
    ok = 1                                        # set to 0 if we encounter division by 0
    small = 1e-12                                 # pivots smaller than this are considered 0
    n = scipy.shape(A)[0]                         # initialize L, U and P
    U = copy.copy(A)
    L = scipy.identity(n)
    P = scipy.identity(n)
    for j in range(1,n):                          # loop over columns
        s = scipy.argmax(abs(U[j-1:n,j-1])) + j -1 # find the largest number in column below diagonal
        if s != j-1:                              # if the largest number is no on the diagonal, swap rows
            U = swap(U,s,j-1,n)
            P = swap(P,s,j-1,n)
            if j>1:
                L = swap(L,s,j-1,j-1)
                
        for i in range(j+1,n+1):                  # check for zero pivot (nearly singular matrix)
            if abs(U[j-1,j-1]) < small:
                print("Near-zero pivot!")
                ok = 0
                break
            L[i-1,j-1] = U[i-1,j-1]/U[j-1,j-1]    # Gauss elimination
            for k in range(j,n+1):
                U[i-1,k-1] = U[i-1,k-1] - L[i-1,j-1] * U[j-1,k-1]
    return L,U,P,ok

def swap(M,i,j,k):
    # Swap rows i and j from column 0 up to (not including) k
    dum = copy.copy(M[i,0:k])
    M[i,0:k] = copy.copy(M[j,0:k])
    M[j,0:k] = copy.copy(dum)
    return M
