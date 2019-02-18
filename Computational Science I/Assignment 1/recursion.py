# Author: Justin Estaris, UOIT 2019.
import math

def recursion(f, g, x, epse, epsr, itmx):
# Iterations of a function g such that g(x)=x iff f(x)=0
# In: function handles f and g, initial point x, error tolerance, residual tolerance, max number of iterations
# Out: approximate solution x, estimate of the error and residual

    y=g(x)
    err=math.fabs(y-x)
    res=math.fabs(f(y))

    print("Current approximation: x=%f err=%e res=%e" % (y,err,res))

    if err < epse and res < epsr:
        print("Convergenced, exiting...")
    else:
        if itmx == 1:
            print("Maximal number of iterations reached")
        else:
            y,err,res = recursion(f, g, y, epse, epsr, itmx-1)

    return y,err,res

