public class Solution {
    private static readonly (int Row, int Col)[] dirs = {(0, 1), (0, -1), (1, 0), (-1, 0)};

    public int ShortestBridge(int[][] grid) {
        int m = grid.Length;
        int n = grid[0].Length;
        Queue<(int I, int J, int Path)> que = new Queue<(int, int, int)>();
        bool marked = false;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    MarkIslandAndSeedQueue(grid, m, n, i, j, que);
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

                if (ni < 0 || ni >= m || nj < 0 || nj >= n || grid[ni][nj] == 2) {
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

    private void MarkIslandAndSeedQueue(int[][] grid, int m, int n, int i, int j, Queue<(int, int, int)> que) {
        grid[i][j] = 2;

        foreach (var dir in dirs) {
            int ni = i + dir.Row;
            int nj = j + dir.Col;

            if (ni < 0 || ni >= m || nj < 0 || nj >= n || grid[ni][nj] == 2) {
                continue;
            }

            if (grid[ni][nj] == 0) {
                grid[ni][nj] = 2;
                que.Enqueue((ni, nj, 1));
                continue;
            }

            MarkIslandAndSeedQueue(grid, m, n, ni, nj, que);
        }
    }
}