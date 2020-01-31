# -*- coding: utf-8 -*-
"""
Created on Tue Oct  1 10:56:39 2019

@author: Ryan Goulding & Justin Estaris

T(n) = T(n/2) + T(n/2) + 5n (or 3n, idk if len counts)
O(n) = 4n
"""

def wordSearch(paragraph, search_word):
    paragraph_length = len(paragraph)
    word_length = len(search_word)
    mid_point = paragraph_length//2
    
    if paragraph_length < word_length:
        return False
    elif paragraph[:word_length] == search_word:
        return True
    else:
        if word_length > mid_point:
            end_point = paragraph_length
        else:
            end_point = mid_point + word_length
        return wordSearch(paragraph[1:end_point],search_word) or wordSearch(paragraph[mid_point:],search_word)
    
search_word = "bstringwi"
paragraph = "You have a long string containing many characters (such as this paragraph), and you want to search for asubstring within this string. For example, one may want to search for “characters” or “want to” or “bstringwi” or “language”. All but the last example should be found."

print("Word Found:", wordSearch(paragraph, search_word))