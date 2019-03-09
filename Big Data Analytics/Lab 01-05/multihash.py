# -*- coding: utf-8 -*-
"""
@author: Justin
"""

from itertools import combinations
import time
import hashlib

start_time = time.time()
#List of baskets
baskets = []
support = 150

candidateList = {}
frequentList = []

hashTable1 = {}
hashTable2 = {} # New

bitMap1 = {}
bitMap2 = {} # New

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
    
#Hash Each pair with Python's built-in hash-function
    #Get pairs for each basket
    pairs = (combinations(basket,2))
    for pair in pairs:
        #Hash each pair
        hashedPair = hash(pair)
        
        #If hashed pair exists in hash table
        if hashedPair in hashTable1:
            hashTable1[hashedPair] += 1 # Increment Value by one
        else:
            hashTable1[hashedPair] = 1 # Add a new entry with a value of 1

#Hash Each pair with a MD5
    #Get pairs for each basket
    pairs = (combinations(basket,2))
    for pair in pairs:
        #Convert Tuple into String
        pairString = ",".join(pair)
        
        #Hash each pair
        hashedPair = hashlib.md5(pairString.encode()).hexdigest()
        
        #If hashed pair exists in hash table
        if hashedPair in hashTable1:
            hashTable2[hashedPair] += 1 # Increment Value by one
        else:
            hashTable2[hashedPair] = 1 # Add a new entry with a value of 1
        
        

#Convert Hashtable1 to Bit Map
for key,value in hashTable1.items():
    #If value is greater than support
    if value >= support:
        bitMap1[key] = 1
    #If value isn't greater than support
    else:
        bitMap1[key] = 0
        
        
#Convert Hashtable2 to Bit Map
for key,value in hashTable2.items():
    #If value is greater than support
    if value >= support:
        bitMap2[key] = 1
    #If value isn't greater than support
    else:
        bitMap2[key] = 0
    
## Pass 2
        
# Read each basket
for basket in baskets:
    # Get pairs for each basket 
    pairs = (combinations(basket,2))
    #Iterate over every pair in pairs
    for pair in pairs:
        #Convert Tuple into String
        pairString = ",".join(pair)
        
        hashedPair1 = hash(pair)
        hashedPair2 = hashlib.md5(pairString.encode()).hexdigest()
        
        #If both elements are frequent
        if candidateList[pair[0]]>=support and candidateList[pair[1]] >= support:
            #If pair is hashed to the frequent bucket
            if bitMap1[hashedPair1] == 1 and bitMap2[hashedPair2] == 1:
                frequentList.append(pair) 
        

#empty candidate list
candidateList.clear()
print("Multihash Support: ", support)
print("My program took", time.time() - start_time, "to run")