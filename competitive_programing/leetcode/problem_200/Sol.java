class Solution {
    public int numIslands(char[][] grid) {
        int c = 0;
        boolean[][] marked = new boolean[grid.length][grid[0].length]; 

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                if (grid[i][j] == '1' && marked[i][j] == false) {
                    c++;
                    this.dfs(i, j, grid, marked);
                }
            }
        }

        marked = null; // Trying to force GC clean marked array

        return c;
    }

    private void dfs(int i, int j, char[][] grid, boolean[][] marked) {
        marked[i][j] = true;

        if (i > 0 && grid[i - 1][j] == '1' && marked[i - 1][j] == false) {
            dfs(i - 1, j, grid, marked);
        }

        if (i < grid.length - 1 && grid[i + 1][j] == '1' && marked[i + 1][j] == false) {
            dfs(i + 1, j, grid, marked);
        }

        if (j > 0 && grid[i][j - 1] == '1' && marked[i][j - 1] == false) {
            dfs(i, j - 1, grid, marked);
        }

        if (j < grid[i].length - 1 && grid[i][j + 1] == '1' && marked[i][j + 1] == false) {
            dfs(i, j + 1, grid, marked);
        }
    }
}
