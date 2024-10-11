def random_logic(x):
    print("Entering random_logic with x =", x)
    i = 0
    while i < 5:
        if x % 2 == 0:
            print("x is even, i =", i)
            if x % 4 == 0:
                print("x is divisible by 4, returning from inside while")
                return "Divisible by 4"
            print("x is even but not divisible by 4")
            x = x + 1
        else:
            print("x is odd, i =", i)
            if x < 0:
                print("x is negative and odd")
                return "Negative odd"
            if x % 3 == 0:
                print("x is divisible by 3")
                return "Divisible by 3"
            if x % 5 == 0:
                print("x is divisible by 5")
                return "Divisible by 5"
            print("x is odd but not divisible by 3 or 5")
            x = x - 2
        i = i + 1
    return "Odd after loop"

def confusing_function(a, b):
    print("Confusing function called with a =", a, "b =", b)
    while a != b:
        if a < b:
            print("a is less than b, a =", a, "b =", b)
            if b - a > 10:
                print("b is much larger than a")
                return "Big difference"
            a = a + 3
        elif a > b:
            print("a is greater than b, a =", a, "b =", b)
            if a % b == 0:
                print("a is divisible by b")
                return "Divisible"
            b = b + 1
    print("a equals b now, returning")
    return "Equal now"

def unpredictable_function(n):
    print("Unpredictable function called with n =", n)
    if n == 0:
        print("n is 0, returning special message")
        return "Zero case"
    while n > 0:
        print("n is positive and n =", n)
        result = random_logic(n)
        print("random_logic result =", result)
        n = n - 3
        if n < 3:
            print("n is now too small, breaking")
            return 0
    if n < 0:
        print("n is negative, calling confusing_function with n =", n)
        return confusing_function(n, -n)
    return "Unpredictable outcome"

def outer_chaos(x, y):
    print("Outer chaos called with x =", x, "y =", y)
    while x != y:
        if x > y:
            print("x is greater than y, x =", x, "y =", y)
            if x - y > 10:
                print("x is much greater than y, returning from unpredictable_function")
                return unpredictable_function(x)
            y = y + 1
        elif x < y:
            print("x is less than y, x =", x, "y =", y)
            if y % 2 == 0:
                print("y is even")
                return confusing_function(x, y)
            x = x + 2
    print("x equals y now, calling random_logic")
    return random_logic(x)

def insanity(a, b):
    print("Entering insanity with a =", a, "b =", b)
    i = 0
    while i < 3:
        if a == 0:
            print("a is zero, i =", i)
            if b == 0:
                print("Both a and b are zero, returning")
                return "Both zero"
            print("Only a is zero, calling outer_chaos")
            return outer_chaos(a, b)
        elif b == 0:
            print("b is zero, i =", i)
            return outer_chaos(a, b)
        elif a == b:
            print("a equals b, i =", i)
            if a % 2 == 0:
                print("Both are even, returning")
                return "Equal evens"
            else:
                print("Both are odd, i =", i)
                if b > 10:
                    print("Calling confusing_function")
                    return confusing_function(a, b)
        else:
            print("a and b are not equal, i =", i)
            if a % b == 0:
                print("a is divisible by b")
                return "Divisible situation"
            elif b % a == 0:
                print("b is divisible by a, calling outer_chaos")
                return outer_chaos(b, a)
        i = i + 1
    print("Loop finished in insanity, calling outer_chaos")
    return outer_chaos(a, b)

print(insanity(10, 5))
print(insanity(0, 0))
print(insanity(8, 12))
print(insanity(15, 15))
print(insanity(25, 50))
