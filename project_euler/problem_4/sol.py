def main() -> None:
    largest : int = 0
    for i in range(999, 0, -1):
        for j in range(i - 1, 0, -1):
            result : int = i * j
            if (str(result) == str(result)[::-1] and result > largest):
                largest = result
    print(largest)


if __name__ == "__main__":
    main()
