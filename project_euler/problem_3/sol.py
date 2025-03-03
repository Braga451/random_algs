# Eratostenes sieve

from math import sqrt

NUM : int = 600851475143

def getPrimesBefore(n : int) -> list[int]:
    limit : int = round(sqrt(n))
    nums : list[bool] = [True for x in range(0, limit)] # This is a little bit wrong because i = 0 and i = 1 are not primes, but meh
    for num in range(2, limit):
        if (nums[num]):
            for i in range(num, round(limit / num)):
                nums[i * num] = False 
    return [i for i in range(2, limit) if nums[i]]

def main() -> None:
    primes : list[int] = getPrimesBefore(NUM)

    for prime in primes[::-1]:
        if (NUM % prime == 0):
            print(prime)
            break

if __name__ == "__main__":
    main()
