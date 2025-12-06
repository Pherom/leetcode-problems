class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<vector<int>>::size_type m = matrix.size();
        vector<int>::size_type n = matrix[0].size();

        bool includeRow = false;
        bool includeCol = false;

        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                includeCol = true;
                break;
            }
        }

        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) {
                includeRow = true;
                break;
            }
        }

        // Mark top-left frame of matrix
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (includeRow) {
            std::fill(matrix[0].begin(), matrix[0].end(), 0);
        }

        if (includeCol) {
            for (int i = 0; i < m; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};