class Solution {
    public boolean isValidSudoku(char[][] board) {
        for (int i = 0; i < 9; i++) {
            boolean[] seen = new boolean[9];

            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    if (seen[Character.getNumericValue(board[i][j]) - 1]) return false;
                    seen[Character.getNumericValue(board[i][j]) - 1] = true;
                }
            }
        }

        for (int j = 0; j < 9; j++) {
            boolean[] seen = new boolean[9];

            for (int i = 0; i < 9; i++) {
                if (board[i][j] != '.') {
                    if (seen[Character.getNumericValue(board[i][j]) - 1]) return false;
                    seen[Character.getNumericValue(board[i][j]) - 1] = true;
                }
            }
        }

        for (int boxes = 0, i = 0, j = 0; boxes < 9; boxes++) {
            if (boxes > 0 && boxes % 3 == 0) {
                i += 3;
                j = 0;
            }
            if (isBoxInvalid(i, j, board)) return false;
            j += 3;
        }

        return true;
    }

    boolean isBoxInvalid(int i, int j, char[][] board) {
        boolean[] seen = new boolean[9];
        for (int iPtr = i; iPtr < i + 3; iPtr++) {
            for (int jPtr = j; jPtr < j + 3; jPtr++) {
                if (board[iPtr][jPtr] != '.') {
                    if (seen[Character.getNumericValue(board[iPtr][jPtr]) - 1]) return true;
                    seen[Character.getNumericValue(board[iPtr][jPtr]) - 1] = true;
                }
            }
        }

        return false;       
    }
}
