def is_prime(n):
    if n <= 1:
        return False
    i = 2
    while i < n:
        if n % i == 0:
            return False
        i = i + 1
    return True

def find_primes_up_to(limit):
    primes = []
    i = 2
    while i <= limit:
        if is_prime(i):
            print(i)
        i = i + 1
    return primes

primes_up_to_10 = find_primes_up_to(100)
