def a(n):
    if n == 1:
        return 1
    return n * a(n - 1)

for i in [1, 2, 3, 4, 5]:
    print(i, a(i))

print([0, 1][1])
print(18)
print([1, 2, 3, 4])

def f(n):
    return 2*n + 1 + 7 // 7

print(1 + 2 + [f(1)][0])
print(2 * 2)
print(4 * 14 + 7 - 8 + 1)

print([i + 1 for i in [0, 1, 2]])
print(type(8), type(5 + 2), type("str"), type([1, 2]), type(False), type(""), type("1"), type([]), type(1 == 1))