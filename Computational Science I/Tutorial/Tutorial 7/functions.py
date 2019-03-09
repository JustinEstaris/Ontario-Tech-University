# Test function for Newton-Raphson iteration, see lecture 8 slide 4. Author: L. van Veen, UOIT, 2019.
import math
import scipy

def f(x):                                                    # First test function: two equations
    y = scipy.zeros((2,1))                                   # Initialize output vector
    y[0] = 2.0 * math.exp(x[0]*x[1]) -2.0*x[0] +2.0*x[1] -2  # Assign function values
    y[1] = x[0]**5 + x[0]* x[1]**5 -2.0*x[1]
    return y

def Df(x):                                                   # Jacobian for first test case
    J = scipy.zeros((2,2))                                   # Initialize as 2-by-2 array
    J[0,0] = 2.0 * x[1] * math.exp(x[0]*x[1]) - 2.0          # Assign values
    J[0,1] = 2.0 * x[0] * math.exp(x[0]*x[1]) + 2.0
    J[1,0] = 5.0 * x[0]**4 + x[1]**5
    J[1,1] = 5.0 * x[0] * x[1]**4 - 2.0
    return J
