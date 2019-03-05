# -*- coding: utf-8 -*-
"""
@author: Justin
"""

from itertools import combinations
import time

start_time = time.time()
#List of baskets
baskets = []
support = 2

candidateList = {}
frequentList = []
hashTable = {}
bitMap = {}


# Setup
file = open("retail.dat")
#For each basket in the file
for basket in file:
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
    
#Iterate over each basket
    #Get pairs for each basket
    pairs = (combinations(basket,2))
    for pair in pairs:
        #Hash each pair
        hashedPair = hash(pair)
        
        #If hashed pair exists in hash table
        if hashedPair in hashTable:
            hashTable[hashedPair] += 1 # Increment Value by one
        else:
            hashTable[hashedPair] = 1 # Add a new entry with a value of 1
        
        
# Read each Dictionary entry
# =============================================================================
# for key,value in candidateList.items():
#     #If value isn't greater than the support
#     if value >= support:
#         # Add item to the frequent list
#         frequentList[key] = value
# =============================================================================




#Convert Hashtable to Bit Map
for key,value in hashTable.items():
    #If value is greater than support
    if value >= support:
        bitMap[key] = 1
    #If value isn't greater than support
    else:
        bitMap[key] = 0
        
        
        
## Pass 2
        
# Read each basket
for basket in baskets:
    # Get pairs for each basket 
    pairs = (combinations(basket,2))
    #Iterate over every pair in pairs
    for pair in pairs:
    
        hashedPair = hash(pair)
        if candidateList[pair[0]]>=support and candidateList[pair[1]] >= support and bitMap[hashedPair] == 1:
            frequentList.append(pair) 
        

#empty candidate list
candidateList.clear()

print("My program took", time.time() - start_time, "to run")