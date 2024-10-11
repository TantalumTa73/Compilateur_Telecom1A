def f():
    a=x+1
    return a

def h():
    x=x+1
    return x

def g():
    x=1
    return x

x=42
print(f())

print(x)
print(g())

print(x)
print(h())
print(x)
