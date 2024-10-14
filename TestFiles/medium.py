
def sub(l, i, j):
    if i == j:
        return []
    return [l[i]] + sub(l, i + 1, j) 

def rev(l):
    if len(l) == 0:
        return []
    return rev(sub(l, 1, len(l))) + [l[0]]

print(rev([0, 1, 2, 3, 4]))