# Functions for the "unknown interest rate problem" in lecture 4.
# Author: L. van Veen, 2018.
import math
def F(i,n,TbyP):                                  # F=0 gives the percentual interest rate i for given number of payments n and ratio of total payment to single payment TbyP.
    return (1.0+i)**n -1.0 -i * (1.0+i)**n * TbyP
def DF(i,n,TbyP):                                 # Derivative of F wrt i.
    return n * (1.0+i)**(n-1) - TbyP * (1.0+i)**n - i * TbyP * n * (1.0+i)**(n-1)
