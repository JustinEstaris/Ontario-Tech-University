# -*- coding: utf-8 -*-
"""
Created on Thu Oct  3 12:01:54 2019

@author: Ryan Goulding & Justin Estaris
"""

def printAsArray(array):
    print(array)

def printAsTree(array, index=0, offset=0):
    left_node = 2*(index+1)-1
    right_node = 2*(index+1)
    array_length = len(array)-1
    
    if left_node <= array_length:
        printAsTree(array, left_node, offset+4)
        
    indent =" "*offset
    print(indent + str(array[index]))
    
    if right_node <= array_length:
        printAsTree(array, right_node, offset+4)

def MaxHeapify(array, index):
    top = array[index]
    l_index = (index*2)+1
    r_index = (index*2)+2
    flag = False
    
    if l_index <= int(len(array)-1):
        l = array[l_index]
    else:
        l = 0
        flag=True
    
    if r_index <= int(len(array)-1):
        r = array[r_index]
    else:
        r = 0
        flag=True
    
    if l > top:
        largest =l
        swap_index = l_index
    else:
        largest = top
    
    if r > largest:
        largest = r
        swap_index = r_index
    
    if largest != top:
        array[index] = largest
        array[swap_index] = top
    
    if flag:
        return
    MaxHeapify(array,index+1)
    
def BuildMaxHeap(array):
    size = len(array)//2
    for i in range(size,-1,-1):
        MaxHeapify(array,i)
        
def HeapMaximum(array):
    return array[0]

def HeapExtractMax(array):
    n=int(len(array)-1)
    if n<1:
        return
    array[0] = array[n]
    array.pop(n)
    MaxHeapify(array,0)

def MaxHeapInsert(array,x):
    array.append(x)
    i = len(array)-1
    parent = (i-1)//2
    while array[i]>array[parent] and i>0:
        temp = array[parent]
        array[parent] = array[i]
        array[i] = temp
        i=parent
        parent = (parent-1)//2
        
    return

def HeapSort(array):
    BuildMaxHeap(array)
    
    for i in range(int(len(array)-1),-1,-1):
        temp = array[1]
        array[1] = array[i]
        array[i] = temp
        MaxHeapify(array,0)

test = [1,2,3,4,7,8,9,10,14,16]
printAsTree(test)
print("\n\n\n")
HeapSort(test)
printAsTree(test)