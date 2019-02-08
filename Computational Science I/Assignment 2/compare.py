#Name: Justin Estaris
#Student ID: 100528069
#Written in collaboration with: Francis Hackenberger, Ryan Goulding, And Andre Dallaire
#Assignment 2

import scipy
from random import randint

def createRow(len(a) ):
    A = scipy.zeros((len(a) , len(a) ))       #Generate 0 matrix
    for m in range(len(a)):
        if (len(a) -m) >= 3:                    #Check condition for a,b,c
            A[m,m]    = randint(-10,10)            #Fill in the diagonal (a values)
            A[m, m+1] = randint(-10,10)         #Fill in the b values
            A[m, m+2] = randint(-10,10)         #Fill in the c values
        elif (len(a) -m) == 2:                  #Check condition for a,b
            A[m,m] = randint(-10,10)            #Fill in the A values
            A[m,m+1] = randint(-10,10)          #Fill in the b values
        else:                                   #Output final a
            A[m,m] = randint(-10,10)            #Fill in the a value
    return A
    
def createColumn(len(a) ):
    A = scipy.zeros((len(a) , 1))          #Generate 0 matrix
    for m in range(len(a) ):
        A[m,0] = randint(0,10)          #Fill in the columns with random values
    return A