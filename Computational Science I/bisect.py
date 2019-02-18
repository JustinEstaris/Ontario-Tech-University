import numpy as np

def F(x,a):
    return x^x - a
	
def bisect(F,a, left,right,k=10,epsx=10**-4,epsF=10**-4):
	results = np.zeros((k,3)) 
	for i in range(k):
		mid = 1/2 * (left +right)
		results[i] = i, right-left, abs(F(mid,a))
		if F(left,a) * F(mid,a) > 0:
			left = mid
		else:
			right = mid
		if(abs(left - right) < epsx) and (abs(F(mid,a)) < epsF):
			return mid, results[:i]
	return mid, results

#Test for part A
theta_c,result1 = bisect(dist, [0.001,9.81,40,100], 1.0,1.4,30,10**-6,10**-6)
print("Answer for part A:",theta_c)