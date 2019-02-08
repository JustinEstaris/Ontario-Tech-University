#Name: Justin Estaris
#Student ID: 100528069
#Written in collaboration with: Francis Hackenberger, Ryan Goulding, And Andre Dallaire
#Assignment 2

import scipy
import numpy
import matplotlib.pyplot as plt
import time
import math
from compare import createRow,createColumn

timeArray = []
timeArray2 = []

def tridag_matvec(column, a, b, c):
    Y = scipy.zeros((len(a) ,1))        #Initialize the zero matrix / resulting matrix

    for m in range(len(a) ):
        if (len(a) - m) >= 3:
            #Matrix dot product
            Y[m,0] = a[m,0] * column[m,0] + b[m,0] * column[m+1,0] + c[m,0] * column[m+2,0]
        elif (len(a) -m) == 2:
            Y[m,0] = a[m,0] * column[m,0] + b[m,0] * column[m+1,0]
        else:
            Y[m,0] = a[m,0] * column[m,0]
    return Y

"""
Question 2c
"""
#Have to lower range to 5, creates a memory error otherwise
#for m in range(2, 8):         
for m in range(2, 5):
    startTime = time.time()

    tridag_matvec(  createColumn(int(math.pow(10, m))), 
                    createColumn(int(math.pow(10,m))), 
                    createColumn(int(math.pow(10,m)) - 1), 
                    createColumn(int(math.pow(10,m)) - 2)
                )
    endTime = time.time()
    timeArray.append(endTime - startTime)
    print("len(a) : " + str(math.pow(10, m)), "\t\tTime: " + str(endTime - startTime))

"""
Question 2d
"""
#Have to lower range to 5, creates a memory error otherwise
#for m in range(2, 8):
for m in range(2, 5):
    startTime = time.time()
    numpy.matmul(numpy.transpose
         (createColumn(int(math.pow(10,m)))), createRow(int(math.pow(10,m))))

    endTime = time.time()
    timeArray2.append(endTime - startTime)
    print("len(a) : " + str(math.pow(10, m)), "\t\tTime: " + str(endTime - startTime))


#lower range by 3 since we cannot generate 6 due to a memory error
#xvalues = range(1,7)
xvalues = range(1,4)
plt.plot(xvalues, timeArray, '-', xvalues, timeArray2, 'g^')  #Plot the values

plt.yscale('log')   #Change the yscale to logarithmic
plt.show            #Show the graphs  