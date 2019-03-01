import math as math

#g(x) from assignment document
def g(x):
    return (1/(2*math.pi))*math.sin(math.pi * x) - (1/(2*math.pi))*(math.pow(x,2)) + x

#Question 1 C
def newtonsIteration(x0, kMax, epsError, epsResidual):
    x_prev = x0             #set previous x to inital x value x(k-1)
    x = g(x0)               #set x to equal the function g with the initial x as its input
    convergence = 0.00      #declare and set convergence to 0.0
    
    #loop from 0 to KMax
    for k in range(0, kMax):
        x_prev = x              #set previous x to current x
        x = g(x)                #calculate new x
        err = abs(x_prev - x)   #calculate absoulte error
        res = abs(x)            #calculate absolute residual
        
        print("Iteration:", str(k), "err:", str(err), "res:", res)
        
        #Check for epsilon values
        if err < epsError and res < epsResidual:
            print("Converged!")
            convergence = 1.00
            break

    #if the loop ends and convergence hasn't changed, we've failed
    if convergence == 0:
        print("Didn't converge")

    return(x, err, res)

#Test some values
print(str(newtonsIteration(1, 50, 1e-7, 1e-7)) + "\n\n")