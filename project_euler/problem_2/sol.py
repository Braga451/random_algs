def fib(limit: int) -> int:
    prev, actual = 1, 1
    sum: int = 0

    while actual <= limit:
        if actual % 2 == 0:
            sum += actual

        prev, actual = actual, (prev + actual)

    return sum


def main() -> None:
    print(fib(4000000))


if __name__ == "__main__":
    main()
