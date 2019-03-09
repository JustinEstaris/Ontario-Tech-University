# Test script for the Newton-Raphson iteration. Author: L. van Veen, UOIT, 2019.
import scipy
import math
from functions import f, Df
import NR

# Initialize the NR parameters
epsf = 1e-13
epsx = 1e-13
kmax = 10
# Initialize x
x0 = scipy.ones([2,1])

x, err, res, conv = NR.NR(f,Df,x0,epsx,epsf,kmax)

# Add output: approximate solution, approximate error and residual.
print("Approximate solution: ")
print("Residual is %d and approximate error is %e \n" % (err,res))