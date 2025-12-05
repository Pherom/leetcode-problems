class Solution {
private:
    array<pair<int, int>, 4> dirs{
        pair<int, int>{0, -1},
        pair<int, int>{1, 0},
        pair<int, int>{-1, 0},
        pair<int, int>{0, 1}
    };

private:
    bool dfs(vector<vector<char>>& board, string const& word, int m, int n, int i, int j, int wordSize, int wordIdx) {
        if (wordIdx == wordSize - 1) {
            return true;
        }
        
        char temp = board[i][j];
        board[i][j] = '*';

        for (pair<int, int> const& dir : dirs) {
            int ni = i + dir.first;
            int nj = j + dir.second;

            if (ni < 0 || ni >= m || nj < 0 || nj >= n || board[ni][nj] != word[wordIdx + 1]) {
                continue;
            }

            if (dfs(board, word, m, n, ni, nj, wordSize, wordIdx + 1)) {
                board[i][j] = temp;
                return true;
            }
        }

        board[i][j] = temp;
        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string const& word) {
        vector<vector<char>>::size_type m = board.size();
        vector<char>::size_type n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0] && dfs(board, word, m, n, i, j, word.size(), 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};