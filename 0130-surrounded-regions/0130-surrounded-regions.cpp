class Solution {
private:
    vector<pair<int, int>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

private:
    void markIgnored(vector<vector<char>>& board, vector<vector<char>>::size_type m, vector<char>::size_type n, int i, int j) {
        board[i][j] = 'I';

        for (pair<int, int> const& dir : dirs) {
            int ni = i + dir.first;
            int nj = j + dir.second;

            if (ni < 0 || ni >= m || nj < 0 || nj >= n || board[ni][nj] != 'O') {
                continue;
            }

            markIgnored(board, m, n, ni, nj);
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        vector<vector<char>>::size_type m = board.size();
        vector<char>::size_type n = board[0].size();

        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O') {
                markIgnored(board, m, n, i, 0);
            }
            
            if (board[i][n - 1] == 'O') {
                markIgnored(board, m, n, i, n - 1);
            }
        }

        for (int j = 0; j < n; ++j) {
            if (board[0][j] == 'O') {
                markIgnored(board, m, n, 0, j);
            }

            if (board[m - 1][j] == 'O') {
                markIgnored(board, m, n, m - 1, j);
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'I') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};