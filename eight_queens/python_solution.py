import time
import copy

def detectQueenInLeftDiagonal(table: list[list[int]], row: int, column: int) -> bool:
    x : int = row - 1
    y : int = column - 1

    while (x != -1 and y != -1):
        if (table[x][y] == 1):
            return True
        
        x -= 1
        y -= 1
    
    x = row + 1
    y = column + 1
    
    while (x != len(table) and y != len(table[x])):
        if (table[x][y] == 1):
            return True

        x += 1
        y += 1

    return False

def detectQueenInRightDiagonal(table: list[list[int]], row: int, column: int) -> bool:
    x : int = row - 1
    y : int = column + 1

    while (x != -1 and y != len(table[x])):
        if (table[x][y] == 1):
            return True

        x -= 1
        y += 1

    x = row + 1
    y = column - 1
    
    while (x != len(table) and y != -1):
        if (table[x][y] == 1):
            return True
        
        x += 1
        y -= 1
    
    return False

def detectQueenInDiagonal(table: list[list[int]], row: int, column: int) -> bool:
    return detectQueenInRightDiagonal(table, row, column) or detectQueenInLeftDiagonal(table, row, column)

def detectQueenInRow(table: list[list[int]], row: int) -> bool:
    for y in range(0, len(table[row])):
        if (table[row][y] == 1):
            return True
    
    return False

def detectQueenInColumn(table: list[list[int]], column: int) -> bool:
    for x in range(len(table)):
        if (table[x][column] == 1):
            return True

    return False

def queens(queensNumber : int, table: list[list[int]], solutions: list[list[list[int]]]) -> None:
    if (queensNumber == 0 and table not in solutions):
        solutions.append(copy.deepcopy(table))
        print(f"[+] Solution found: {table}") 
        return
    
    for x in range(0, len(table)):
        if (not detectQueenInRow(table, x)):
            for y in range(0, len(table[x])):
                if (not detectQueenInColumn(table, y) and not detectQueenInDiagonal(table, x, y)):
                    table[x][y] = 1
                    queens(queensNumber - 1, table, solutions)
                    table[x][y] = 0
    
def main() -> None:
    solutions : list[list[list[int]]] = []
    table : list[list[int]] = [[0 for x in range(0, 8)] for x in range(0, 8)]
    
    start_time = time.time()

    queens(8, table, solutions)

    print(f"Exec time: {time.time() - start_time}")

    with open("result.log", "w") as log:
        log.write(f"Number of solutions: {len(solutions)}\n")
        log.write(f"Solutions:\n{solutions}\n")
        log.close()
    
if __name__ == "__main__":
    main()
