#Authors: Justin Estaris & Ryan Goulding

# s1 = String 1
# s2 = String 2
# n = Length of String 1
# m = Length of String 2
def med(s1, s2, n, m):
    # If there's no first string
    if n == 0:
        return m  # Must insert all string 2 characters to match

    # If there's no second string
    if m == 0:
        return n  # Must delete all string 1 characters to match string 2

    # Check if the last characters are the same, if yes then go to the next letter (right to left)
    if s1[n - 1] == s2[m - 1]:
        return med(s1, s2, n - 1, m - 1)

    # If the letters aren't the same
    else:
        return 1 + min(med(s1, s2, n, m - 1),       # Insert
                       med(s1, s2, n - 1, m),       # Remove
                       med(s1, s2, n - 1, m - 1))   # Replace


s1_test = ["spoof", "podiatrist", "blaming", "Justin", "test", " ", "CSCI"]
s2_test = ["stool", "pediatrician", "conning", "Ryan", " ", "test2", "CSCI"]

for i in range(len(s1_test)):
    med_result = med(s1_test[i], s2_test[i], len(s1_test[i]), len(s2_test[i]))
    print("The Minimum Edit Distance from", s1_test[i], "to", s2_test[i], "is:", med_result)

