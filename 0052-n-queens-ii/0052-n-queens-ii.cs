public class Solution {
    public int TotalNQueens(int n) {
        var placedQueens = new List<(int R, int C)>(n);

        int rec(int row) {
            if (row == n) {
                return 1;
            }

            int count = 0;

            for (int col = 0; col < n; ++col) {
                bool conflict = false;

                foreach (var (otherRow, otherCol) in placedQueens) {
                    if (otherCol == col || otherCol + otherRow == col + row || otherCol - otherRow == col - row) {
                        conflict = true;
                        break;
                    }
                }

                if (conflict) {
                    continue;
                }

                placedQueens.Add((row, col));
                count += rec(row + 1);
                placedQueens.RemoveAt(placedQueens.Count - 1);
            }

            return count;
        }

        return rec(0);
    }
}