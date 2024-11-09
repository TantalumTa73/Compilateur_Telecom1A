a = 2
b = 3
c = 2
d = 5

T = [0 for _ in range(a * (1 + b * (1 + c * (1 + d))))]

sz = 1

base_pointer = 0
# for i in range(a):
#     T[i] = base_pointer + sz*(a + b*i)

# for i in range(a*b):
#     T[sz*a + i] = base_pointer + sz*(a + a*b + c*i)

# for i in range(a*b*c):
#     T[sz*(a + a*b) + i] = base_pointer + sz*(a + a*b + a*b*c + d*i)

el = [2, 3, 2, 5]
layers = len(el)

m = el[0]
p = 0

for l in range(layers - 1):
    j = base_pointer - sz * p
    k = sz * el[l + 1]
    q = base_pointer + sz * (p + m)
    for i in range(m):
        T[j] = q
        j = j - sz
        q = q + k
    p = p + m
    m = m * el[l + 1]

"""
# initial
mov {T_address}, %r8
mov ${v0}, %r9
mov $0, %r10

# looping for first layer
mov ${sz}, %r11
imul %r10, %r11

mov ${sz}, %r12
imul ${v[l+1]}, %r12

mov %r10, %r13
add %r9, %r13
imul ${sz}, %r13
add %r8, %r13

mov $0, %r15
loop_n_dimensional_in_{l}_{which}:

cmp %r15, %r9
jge loop_n_dimensional_out_{l}_{which}

mov %r13, (%r11)
add ${sz}, %r11
add %r12, %r13

add $1, %r15

loop_n_dimensional_out_{l}_{which}:

add %r9, %r10
imul ${v(l+1)}, %r9
"""

print(T)