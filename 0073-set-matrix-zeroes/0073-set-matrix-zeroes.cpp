class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<vector<int>>::size_type m = matrix.size();
        vector<int>::size_type n = matrix[0].size();

        vector<bool> markedRows(m, false);
        vector<bool> markedCols(n, false);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    markedCols[j] = true;
                    markedRows[i] = true;
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (markedCols[j] || markedRows[i]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};