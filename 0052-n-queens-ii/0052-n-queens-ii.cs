public class Solution {
    public int TotalNQueens(int n) {
        var placedQueens = new int[n];

        int rec(int row) {
            if (row > n) {
                return 1;
            }

            int count = 0;

            for (int col = 1; col <= n; ++col) {
                bool conflict = false;

                for (int otherRow = 1; otherRow < row; ++otherRow) {
                    int otherCol = placedQueens[otherRow - 1];

                    if (otherCol == col || otherCol + otherRow == col + row || otherCol - otherRow == col - row) {
                        conflict = true;
                        break;
                    }
                }

                if (conflict) {
                    continue;
                }

                placedQueens[row - 1] = col;
                count += rec(row + 1);
                placedQueens[row - 1] = 0;
            }

            return count;
        }

        return rec(1);
    }
}