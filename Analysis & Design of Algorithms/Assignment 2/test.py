#Authors: Justin Estaris & Ryan Goulding

#Pseudocode for Huffman Algorithm

#Step 0. Read ASCII File
file = open("test.txt","r")
fileString = (file.read())


#Step 0.5. Convert File Input into a character array
characterArray = list(fileString)
print("Character Array is:")
print(characterArray)

#Step 1. Create Frequency Table
characterFrequencyTable = {}

for char in characterArray:
    if char in characterFrequencyTable:
        characterFrequencyTable[char] += 1
    else:
        characterFrequencyTable[char] = 1

print("Frequency Table is:")
print(characterFrequencyTable)


#Step 2. Create Huffman Tree
    # Step 2.1 - Create a forest of single-node trees (character and count)

#Pseudocode
# C =

# Procedure Huffman(C):     // C is the set of n characters and related information
# n = C.size
# Q = priority_queue()
# for i = 1 to n
#     n = node(C[i])
#     Q.push(n)
# end for

# while Q.size() is not equal to 1
#     Z = new node()
#     Z.left = x = Q.pop
#     Z.right = y = Q.pop
#     Z.frequency = x.frequency + y.frequency
#     Q.push(Z)
# end while
# Return Q
