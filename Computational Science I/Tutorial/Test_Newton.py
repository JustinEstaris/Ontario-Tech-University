import scipy
import math
import matplotlib.pyplot as plt
from UIRP import *
from Newton_method import Newton

# Set parameters
n = 12.0
TbyP = 10.0

# Plot to estimate where the solution is
xs = scipy.linspace(0,0.1,100)
ys = F(xs,n,TbyP)
plt.plot(xs,ys)
plt.plot([0.,0.1],[0.,0.])
plt.show()

# Set initial point
x0 = 0.014

# Set Newton parameters
kmax = 6
tolx = 1e-14
tolf = 1e-14

# Re-define the function and its derivative to have a single input
def f(x):
    return F(x,n,TbyP)
def df(x):
    return DF(x,n,TbyP)

# Call Newton
x, err, res = Newton(f,df,x0,tolx,tolf,kmax)
