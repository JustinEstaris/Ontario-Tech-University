# Authors: Justin Estaris & Ryan Goulding

from heapq import heapify, heappop, heappush


# Test the algorithm
def huffman(C):
    # Initialize Encoded Length
    originalLength = 0
    encodedLength = 0

    # Get contents of ASCII text File
    with open(C, 'r') as file:
        n = file.read().replace('\n', '') #Converted file contents into a string
        originalLength = (len(n) * 8)  # Get Length of File
    file.close

    # Step 0. Create frequency table
    charFreq = {}
    for character in n:
        if character in charFreq:
            charFreq[character] += 1
        else:
            charFreq[character] = 1

    # Step 1. Create Heap
    heap = [[freq, [char, '']] for char, freq in charFreq.items()]
    heapify(heap)  # Transform list into heap

    # Step 2. Create Huffman Tree
    while len(heap) > 1:
        zLeft = heappop(heap)  # Pop and return the smallest item from the heap - call it left
        zRight = heappop(heap)  # Pop and return the smallest item from the heap - call it right
        leftNodes = zLeft[1:]  #All the "left" nodes
        rightNodes = zRight[1:]  #All the "right" nodes
        freqVal = zLeft[0] + zRight[0]  #Combine Left and Right node frequency values
        combinedNode = leftNodes + rightNodes  #Combine left and right node character values

        # 2.1 Get Left and Right Node and Append 0 or 1 to the node
        # For every left node
        for node in leftNodes:
            node[1] = '0' + node[1]  # Add the Number 0 to the prefix for every node ['char','prefix']

        # For every right node
        for node in rightNodes:
            node[1] = '1' + node[1]  # Add the Number 1 to the prefix for every node ['char','prefix']

        # 2.2 Combine the left and right nodes values (Character frequency and Characters)
        # Insert new item to the heap
        #   Combined the freq values of the left and right node
        #   Combined left and right into a single node
        heappush(heap, [freqVal] + combinedNode)

    codes = sorted(heappop(heap)[1:], key=lambda prefix: (len(prefix[-1]), prefix))

    # Step 4. Create Table
    print("The Huffman Code: ")

    for i in codes:
        character = i[0]
        frequency = str(charFreq[i[0]])
        prefix = i[1]

        print("Data:", character, ",", "Frequency:", frequency, ",", "Prefix Code:", prefix)
        encodedLength += (len(prefix) * 2)

    # Step 5. Calculate Length of the entire document before and after prefix codes
    print("\nOriginal length: ", originalLength, "bits")
    print("Encoded length:  ", encodedLength, "bits")


file = input("Enter file name: ")
huffman(file)
