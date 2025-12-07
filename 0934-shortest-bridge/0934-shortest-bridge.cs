public class Solution {
    private Tuple<int, int>[] dirs = {
        new Tuple<int, int>(0, 1),
        new Tuple<int, int>(0, -1),
        new Tuple<int, int>(1, 0),
        new Tuple<int, int>(-1, 0)
    };

    public int ShortestBridge(int[][] grid) {
        Queue<Tuple<int, int, int>> que = new Queue<Tuple<int, int, int>>();
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
            int i = que.Peek().Item1;
            int j = que.Peek().Item2;
            int path = que.Peek().Item3;
            que.Dequeue();

            foreach (Tuple<int, int> dir in dirs) {
                int ni = i + dir.Item1;
                int nj = j + dir.Item2;

                if (ni < 0 || ni >= grid.Length || nj < 0 || nj >= grid[0].Length || grid[ni][nj] == 2) {
                    continue;
                }

                if (grid[ni][nj] == 1) {
                    return path;
                }

                grid[ni][nj] = 2;
                que.Enqueue(new Tuple<int, int, int>(ni, nj, path + 1));
            }
        }

        return 0;
    }

    private void markCoasts(int[][] grid, int i, int j, Queue<Tuple<int, int, int>> que) {
        grid[i][j] = 2;

        foreach (Tuple<int, int> dir in dirs) {
            int ni = i + dir.Item1;
            int nj = j + dir.Item2;

            if (ni < 0 || ni >= grid.Length || nj < 0 || nj >= grid[0].Length || grid[ni][nj] == 2) {
                continue;
            }

            if (grid[ni][nj] == 0) {
                que.Enqueue(new Tuple<int, int, int>(i, j, 0));
                continue;
            }

            markCoasts(grid, ni, nj, que);
        }
    }
}