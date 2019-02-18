# Author: Justin Estaris, UOIT 2019.
import math
import scipy

def steff(f,fp,x,epse,epsr,itmx):
# Steffensen iteration for f(x)=0.
#   Input: f, f', intial point x, error tolerance, residual tolerance, max nr of iterations
#   Output: approximate solution x, estimate of error, residual
    conv=0                                             # flag for convergence
    xs = scipy.zeros((3))
    for i in range(0,itmx):
        xs[0] = x
        dx = -f(x)/fp(x)                               # first Newton step
        x = x+dx
        xs[1]=x
        dx = -f(x)/fp(x)                               # second Newton step
        x = x+dx
        xs[2] = x
        x=xs[0]-(xs[1]-xs[0])**2/(xs[2]-2.0*xs[1]+xs[0]) # Steffensen's formula
        err=math.fabs(x-xs[0])                         # estimate of the error
        res=math.fabs(f(x))                            # residual
        print("Iteration %d x=%f err=%e res=%e" % (i,x,err,res))
        if err < epse and res < epsr:
            print("Converged, exiting...")
            conv = 1
            break
    if conv == 0:
        print("No convergence!")
    return x,err,res


