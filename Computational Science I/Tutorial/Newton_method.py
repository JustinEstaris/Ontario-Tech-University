import math as math

#function
def F(x):
    return x**(-x+4)-x**2

#derived function
def dF(x):
    return x**(4-x)*(((4-x)/x)-math.log(x))-2*x

def Newton(f,df,x0,tolf,tolx,kmax):
    x = x0
    conv = 0
    for i in range(1,kmax+1):
        r = f(x)
        dx = -r/df(x)
        x = x + dx
        err = abs(dx)
        res = abs(r)
        print('it=%d x=%e err=%e res=%e' % (i,x,err,res))
        if err < tolx and res < tolf:
            conv = 1
            break
    if conv == 0:
        print('No convergence!')
    return x,err,res

#Test some values
print(str(Newton(F, dF, 4, 10**-5,10**-5,25)) + "\n\n")


## STRAIGHT FROM VEEN: ##
# def Newton(f,df,x0,tolf,tolx,kmax):
#     x = x0
#     conv = 0
#     for i in range(1,kmax+1):
#         r = f(x)
#         dx = -r/df(x)
#         x = x + dx
#         err = abs(dx)
#         res = abs(r)
#         print('it=%d x=%e err=%e res=%e' % (i,x,err,res))
#         if err < tolx and res < tolf:
#             conv = 1
#             break
#     if conv == 0:
#         print('No convergence!')
#     return x,err,res
