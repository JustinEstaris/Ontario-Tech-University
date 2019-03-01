# -*- coding: utf-8 -*-
"""
Created on Fri Mar  1 08:52:22 2019
Program to Create and Solve a Vandermonde Matrix

@author: Justin
"""

import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt

def makeVandermonde(n,x):
    V = np.ones((n,n))
    for i in range(1,n):
        V[:,i] = x**i
    return V

def P(x,a):
    n = a.shape[0]-1
    poly = a[n-1]+a[n]*x
    for k in range(n-2,-1,-1):
        poly = a[k]+poly * x
    return poly

n_min = 4
n_max = 4

for n in range(n_min,n_max+1):
    x = np.array([i  for i in range(n)])
    y = np.exp(x)

    V = makeVandermonde(n,x)
    
    a = la.solve(V,y)
    
    xc = np.linspace(0, n, 1000)
    yc = np.zeros(xc.shape)
    for k in range(len(xc)):
        yc[k] = P(xc[k],a)
        
    plt.figure()
    plt.plot(xc,yc,'r--',x,y,'b.')  
    plt.show()
         