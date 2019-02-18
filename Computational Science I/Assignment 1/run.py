# Author: Justin Estaris, UOIT 2019. Solutions for assignment 1.
import math
from iteration import iteration
from recursion import recursion
from steffensen import steff
from newton import newton

# question 1
def g(x):
    return (math.sin(math.pi * x) -x**2)/(2.0 * math.pi) + x

def f(x):
    return math.sin(math.pi * x) - x**2

# tolerances and number of iterations
tol_err = 1e-5
tol_res = 1e-5
itmax = 20

# try different initial points
x0 = 1.0
print("Trying initial point %f..." % (x0))
x,err,res = iteration(f, g, x0, tol_err, tol_res, itmax)

x0 = 0.0
print("Trying initial point %f..." % (x0))
x,err,res = iteration(f, g, x0, tol_err, tol_res, itmax)

x0 = -0.1
print("Trying initial point %f..." % (x0))
x,err,res = iteration(f, g, x0, tol_err, tol_res, itmax)
# in the final run, the approximate solutions approaches minus infinity...

# now call the recursively programmed function
x0 = 1.0
print("Trying initial point %f with recursion..." % (x0))
x,err,res = recursion(f, g, x0, tol_err, tol_res, itmax)


# question 2 - Naming conflict with question 1. Comment Q1 and Uncomment code below to get answer.
#def f(x):
#    return math.exp(x-x**2)-x/2.0-1.0836
def fp(x):
    return (1.0-2.0*x)*math.exp(x-x**2)-0.5

# residual and error tolerance, number of iterations
tol_err = 1e-10
tol_res = 1e-10
itmax = 10

# initial point
x0 = 1.0

# first try Newton iteration
print("Calling Newton function...")
x,err,res = newton(f,fp,x0,tol_res,tol_err,itmax)
# that converges slowly, now try steffenson
print("Calling Steffensen function...")
x,err,res = steff(f,fp,x0,tol_err,tol_res,itmax)
