def a(n):
    if n == 1:
        return 1
    return n * a(n - 1)

for i in [1, 2, 3, 4, 5]:
    print(i, a(i))

print([0, 1][1])
print(18)
print([1, 2, 3, 4])