# Authors: Francis Hackenbergert & Andre Dallaire

import heapq

def huffman_coding(frequency):
    heap = [[freq, [char, '']] for char, freq in frequency.items()]
    heapq.heapify(heap)  #Transform list into heap


    while len(heap) > 1:
        print("heap: ", heap)
        left = heapq.heappop(heap)  # Pop and return the smallest item from the heap - call it left
        print("Selected left Node: ", left)
        right = heapq.heappop(heap)  # Pop and return the smallest item from the heap - call it right
        print("Selected right Node: ", right)


        leftNodes = left[1:]
        print("left 1: ", left[1:])
        for node in leftNodes:
            node[1] = '0' + node[1]  # Add the Number 0 to the prefix
            print("Added 0: ", node)

        print("\n\nright 1:", right[1:])
        for node in right[1:]:
            node[1] = '1' + node[1]  # Add the Number 1 to the prefix ['char','prefix']
            print("Added 1: ", node)

        # Push new item to the heap
        # Combine the freq values of the left and right node
        #
        heapq.heappush(heap, [left[0] + right[0]] + left[1:] + right[1:])

    return sorted(heapq.heappop(heap)[1:], key=lambda prefix: (len(prefix[-1]), prefix))


# Test the algorithm
def huffman(filename):

    # Initialize string variable
    string = ""

    #Open Filename
    with open(filename, 'r') as textFile:
        string = textFile.read().replace('\n', '')

    # Get frequencies of each character
    freq = {}
    for character in string:
        if character in freq:
            freq[character] += 1
        else:
            freq[character] = 1

    prefixCodes = huffman_coding(freq)

    # # Create Header of Character, Frequency and Prefix Code
    #print("Char".ljust(5) + "Freq".ljust(5) + "Prefix Code")
    #
    # #Loop over every prefix value of the array
    # for prefix in prefixCodes:
    #     print(prefix[0].ljust(5) + str(freq[prefix[0]]).ljust(5) + prefix[1])
    #
    # print("Original length: ", len(string))
    # print("Encoded length: ", len(prefixCodes))


fileName = input("Enter a filename: ")
huffman(fileName)