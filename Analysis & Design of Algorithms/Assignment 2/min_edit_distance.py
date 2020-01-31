#Authors: Francis Hackenbergert & Andre Dallaire

def min_edit_distance(first_string, second_string):
    m = len(first_string)
    n = len(second_string)


    D = [[0 for i in range(n + 1)]
            for i in range(m + 1)]
#     print(range(n))
#     print(range(n+1))
#     print(D)
#
# min_edit_distance("ab","ab")

    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0:
                D[i][j] = j
            elif j == 0:
                D[i][j] = i
            elif first_string[i - 1] == second_string[j - 1]:
                D[i][j] = D[i - 1][j - 1]
            else:
                D[i][j] = 1 + min(D[i][j - 1],      # insertion
                                  D[i - 1][j],      # deletion
                                  D[i - 1][j - 1])  # substitution
    #print(D)
    return D[m][n]

# Sample test inputs from Assignment requirements
first_strings = ["spoof", "podiatrist", "blaming"]
second_strings = ["stool", "pediatrician", "conning"]

for i in range(len(first_strings)):
    print(min_edit_distance(first_strings[i], second_strings[i]))