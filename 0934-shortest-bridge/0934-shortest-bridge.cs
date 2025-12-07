public class Solution {
    private (int Row, int Col)[] dirs = {(0, 1), (0, -1), (1, 0), (-1, 0)};

    public int ShortestBridge(int[][] grid) {
        Queue<(int I, int J, int Path)> que = new Queue<(int, int, int)>();
        bool marked = false;

        for (int i = 0; i < grid.Length; ++i) {
            for (int j = 0; j < grid[0].Length; ++j) {
                if (grid[i][j] == 1) {
                    markCoasts(grid, i, j, que);
                    marked = true;
                    break;
                }
            }

            if (marked) {
                break;
            }
        }

        while (que.Count() != 0) {
            var curr = que.Dequeue();

            foreach (var dir in dirs) {
                int ni = curr.I + dir.Row;
                int nj = curr.J + dir.Col;

                if (ni < 0 || ni >= grid.Length || nj < 0 || nj >= grid[0].Length || grid[ni][nj] == 2) {
                    continue;
                }

                if (grid[ni][nj] == 1) {
                    return curr.Path;
                }

                grid[ni][nj] = 2;
                que.Enqueue((ni, nj, curr.Path + 1));
            }
        }

        return 0;
    }

    private void markCoasts(int[][] grid, int i, int j, Queue<(int, int, int)> que) {
        grid[i][j] = 2;

        foreach (var dir in dirs) {
            int ni = i + dir.Row;
            int nj = j + dir.Col;

            if (ni < 0 || ni >= grid.Length || nj < 0 || nj >= grid[0].Length || grid[ni][nj] == 2) {
                continue;
            }

            if (grid[ni][nj] == 0) {
                que.Enqueue((i, j, 0));
                continue;
            }

            markCoasts(grid, ni, nj, que);
        }
    }
}