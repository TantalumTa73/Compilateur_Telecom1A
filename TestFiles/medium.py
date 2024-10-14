
def sub(l, i, j):
    if i == j:
        return []
    a = [l[i]]
    b = sub(l, i + 1, j)
    return a + b 

def rev(l):
    if len(l) == 0:
        return []
    return rev(sub(l, 1, len(l))) + [l[0]]

print(rev([0, 1, 2, 3, 4]))