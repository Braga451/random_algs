def main() -> None:
    max_3: int = int(1000 / 3)
    max_5: int = int(1000 / 5)
    sum_set: set[int] = set()
    sum: int = 0
    for i in range(1, max_3 + 1):
        sum_set.add(i * 3)
        if i < max_5:
            sum_set.add(i * 5)

    for v in sum_set:
        sum += v

    print(sum)


if __name__ == "__main__":
    main()
