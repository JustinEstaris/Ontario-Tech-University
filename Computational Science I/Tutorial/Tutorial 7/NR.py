# Not-yet-finished implementation of Newton-Raphson iteration. See lecture 8 and tutorial 7. Author: L. van Veen, UOIT, 2019.
# Newton-Raphson iteration
import math
import scipy
import scipy.linalg

def NR(f,Df,x0,epsx,epsf,kmax):
        conv = 0
        x=scipy.matrix(x0)
        x = scipy.matrix(x0)
        for k in range(0,kmax):
                r = -f(x)
                J = Df(x)
                # next step: solve the linear system J dx = r
                dx = scipy.linalg.solve(J,r)

                # next step: update the approximate solution as x <- x + dx
                x += dx

                # next step: compute the approximate error |dx| and the residual |f(x)|
                err = scipy.linalg.norm(dx,2)
                res = scipy.linalg.norm(r,2)
                # next step: print the error and residual to the screen
                print("Iteration = %d, Error = %d, Residual = %d \n" % (k,err,res))

                # next step: check if the error and residual are less than their respective thresholds and, if so, exit the loop        
                if err < epsx and res < epsf:
                        conv = 1
                        break
        if conv == 0:
                print("Not Converged \n")
