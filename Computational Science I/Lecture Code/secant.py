import math
import numpy as np

def secant(F, a, x0, x1, k = 10, epsx = 10**-4, epsf = 10**-4):
    results = np.zeros((k, 3))

    for i in range(k):
        x_new = x1 - F(x1, a) * (x1 - x0) / (F(x1, a) - F(x0, a))
        results[i] = i, abs(x_new - x1), abs(F(x_new, a))
        if (abs(x_new - x1) < epsx) and (abs(F(x_new, a)) < epsf):
            return x_new, results[:i]
        
        x0 = x1
        x1 = x_new
    print("Iterations did not converge!")
    return x_new, results