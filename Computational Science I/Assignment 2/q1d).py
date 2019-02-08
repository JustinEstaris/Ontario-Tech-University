## Author: Justin Estaris 100528069
## Code written in collaboration with Ryan Goulding, Francis Hackenberger and Andre Dallaire
## Assignment 2

import scipy
from numpy import linalg as lin

C = [[2,0],[50,1]]




# Q1 d)
print("The condition number is: " + lin.cond(C).astype(str))

""" 
	- The condition number = 1252. 
	- Can compute x up to an accuracy of 2 digits.
"""