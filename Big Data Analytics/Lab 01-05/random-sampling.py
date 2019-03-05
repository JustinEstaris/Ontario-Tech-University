# -*- coding: utf-8 -*-
"""

@author: Justin Estaris
"""
from itertools import combinations
import random
import time

start_time = time.time()
#List of baskets
baskets = []
support = 50
lineCount = 0
threshold = 0.05 #5%
sampleSize = 0
candidateList = {}
frequentList = {}


# Setup
file = open("retail.dat")


#Get File Length
for basket in file:
    lineCount += 1
    

#Get Sample Size
sampleSize = int(lineCount * threshold)

#Get Sample     

with open('retail.dat') as f:
    lines = random.sample(f.readlines(),sampleSize)

for line in lines:
    baskets.append(line.split())

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