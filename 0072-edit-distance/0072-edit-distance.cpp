class Solution {
// private:
//     int minDistanceRec(string_view word1, string_view word2, size_t n1, size_t n2, size_t i1, size_t i2) {
//         if (i2 == n2) {
//             return n1 - i1;
//         }

//         if (i1 == n1) {
//             return n2 - i2;
//         }

//         if (word1[i1] == word2[i2]) {
//             return minDistanceRec(word1, word2, n1, n2, i1 + 1, i2 + 1);
//         }

//         return 1 + min(minDistanceRec(word1, word2, n1, n2, i1 + 1, i2), min(minDistanceRec(word1, word2, n1, n2, i1, i2 + 1), minDistanceRec(word1, word2, n1, n2, i1 + 1, i2 + 1)));
//     }

public:
    int minDistance(string_view word1, string_view word2) {
        // return minDistanceRec(word1, word2, word1.size(), word2.size(), 0, 0);

        size_t n1 = word1.size();
        size_t n2 = word2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));

        for (int j = 0; j <= n2; ++j) {
            dp[n1][j] = n2 - j;
        }

        for (int i = 0; i <= n1; ++i) {
            dp[i][n2] = n1 - i;
        }

        for (int i = n1 - 1; i >= 0; --i) {
            for (int j = n2 - 1; j >= 0; --j) {
                if (word1[i] == word2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                    continue;
                }

                dp[i][j] = 1 + min(dp[i + 1][j], min(dp[i + 1][j + 1], dp[i][j + 1]));
            }
        }

        return dp[0][0];
    }
};