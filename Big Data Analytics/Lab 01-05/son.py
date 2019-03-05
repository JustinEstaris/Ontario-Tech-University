# -*- coding: utf-8 -*-
"""
Created on Tue Mar  5 15:13:55 2019

@author: Justin
"""

# -*- coding: utf-8 -*-
"""

@author: Justin Estaris
"""
from itertools import combinations
import time

start_time = time.time()
#List of baskets
baskets = []
support = 50
sampleSize = 1000

candidateList = {}
frequentList = {}


# Setup
file = open("retail.dat")

#For each basket in the file
for basket in file:

    if len(baskets) < sampleSize:
        # Convert each line as a CSV List and Append it 
        baskets.append(basket.split())

## Pass 1
#Read each basket
for basket in baskets:
    #Read each element
    for item in basket:
        # If element exists in the candidateList
        if item in candidateList:
            #Increment Count by 1
            candidateList[item] += 1
        # else element doesn't exist in the candidateList
        else:
            # Create Entry with a starting value of 1
            candidateList[item] = 1 
        
        
# Read each Dictionary entry
for key,value in candidateList.items():
    #If value isn't greater than the support
    if value >= support:
        # Add item to the frequent list
        frequentList[key] = value

#empty candidate list
candidateList.clear()


## Pass 2
# Read each basket
for basket in baskets:
    # Get pairs for each basket 
    pairs = (combinations(basket,2))
    #Iterate over every pair in pairs
    for pair in pairs:
        #Convert Tuple into String
        pairString = ",".join(pair)
        
        if pairString in candidateList:
            #Increment Count by 1
            candidateList[pairString] += 1
        # else element doesn't exist in the candidateList
        else:
            # Create Entry with a starting value of 1
            candidateList[pairString] = 1 

for key,value in candidateList.items():
    #If value isn't greater than the support
    if value >= support:
        # Add item to the frequent list
        frequentList[key] = value

#empty candidate list
candidateList.clear()

print("My program took", time.time() - start_time, "to run")