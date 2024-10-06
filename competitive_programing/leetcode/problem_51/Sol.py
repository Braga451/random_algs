from threading import Thread
import copy


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        board: list[list[str]] = [["." for i in range(n)] for i in range(n)]
        banned_cols: dict[int, bool] = dict.fromkeys(range(n), False)
        sols: list[list[list[str]]] = []
        threads: list[Thread] = []
        self.__backtracking(n, board, banned_cols, sols, 0, -1, threads)

        for t in threads:
            t.join()

        return sols

    def __backtracking(
        self,
        n: int,
        board: list[list[int]],
        banned_cols: dict[int, bool],
        sols: list[list[list[str]]],
        q: int,
        prev_i: int,
        process_list: list[Thread],
    ) -> None:
        if q == n:
            sol: list[list[str]] = ["".join(w) for w in board]
            sols.append(sol)
            return

        for i in range(prev_i + 1, n):
            if prev_i == -1 and i != 0:
                return

            for j in range(n):
                if prev_i == -1:
                    board[i][j] = "Q"
                    banned_cols[j] = True
                    t: Thread = Thread(
                        target=self.__backtracking,
                        args=[
                            n,
                            copy.deepcopy(board),
                            banned_cols.copy(),
                            sols,
                            q + 1,
                            i,
                            [],
                        ],
                    )
                    banned_cols[j] = False
                    board[i][j] = "."
                    process_list.append(t)
                    t.start()
                    continue

                if banned_cols[j] == True:
                    continue

                banned_cols[j] = True

                if self.__verifyDiagonals(i, j, n, board) == False:
                    board[i][j] = "Q"
                    self.__backtracking(n, board, banned_cols, sols, q + 1, i, [])
                    board[i][j] = "."

                banned_cols[j] = False

    def __verifyDiagonals(self, i: int, j: int, n: int, board: list[list[str]]) -> bool:
        return self.__verifyLeftDiagonal(i, j, n, board) or self.__verifyRightDiagonal(
            i, j, n, board
        )

    def __verifyLeftDiagonal(
        self, i: int, j: int, n: int, board: list[list[str]]
    ) -> bool:
        tmp_i: int = i
        tmp_j: int = j

        while tmp_i >= 0 and tmp_j >= 0:
            if board[tmp_i][tmp_j] == "Q":
                return True

            tmp_i -= 1
            tmp_j -= 1

        tmp_i: int = i
        tmp_j: int = j

        while tmp_i < n and tmp_j < n:
            if board[tmp_i][tmp_j] == "Q":
                return True

            tmp_i += 1
            tmp_j += 1

        return False

    def __verifyRightDiagonal(
        self, i: int, j: int, n: int, board: list[list[str]]
    ) -> bool:
        tmp_i: int = i
        tmp_j: int = j

        while tmp_i >= 0 and tmp_j < n:
            if board[tmp_i][tmp_j] == "Q":
                return True

            tmp_i -= 1
            tmp_j += 1

        tmp_i: int = i
        tmp_j: int = j

        while tmp_i < n and tmp_j >= 0:
            if board[tmp_i][tmp_j] == "Q":
                return True

            tmp_i += 1
            tmp_j -= 1

        return False
