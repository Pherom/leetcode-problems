public class Solution {
    // Recursive Approach:

    // public int MinDistance(string word1, string word2) {
    //     int n1 = word1.Length;
    //     int n2 = word2.Length;

    //     int rec(int i1, int i2) {
    //         if (i1 == n1) {
    //             return n2 - i2;
    //         }

    //         if (i2 == n2) {
    //             return n1 - i1;
    //         }

    //         if (word1[i1] == word2[i2]) {
    //             return rec(i1 + 1, i2 + 1);
    //         }

    //         return 1 + Math.Min(rec(i1 + 1, i2 + 1), Math.Min(rec(i1 + 1, i2), rec(i1, i2 + 1)));
    //     }

    //     return rec(0, 0);
    // }

    // Dynamic Programming:
    public int MinDistance(string word1, string word2) {
        int n1 = word1.Length;
        int n2 = word2.Length;
        var dp = new int[2, n2 + 1];

        for (int j = 0; j <= n2; ++j) {
            dp[1, j] = n2 - j;
        }

        for (int i = n1 - 1; i >= 0; --i) {
            dp[0, n2] = n1 - i;

            for (int j = n2 - 1; j >= 0; --j) {
                if (word1[i] == word2[j]) {
                    dp[0, j] = dp[1, j + 1];
                    continue;
                }

                dp[0, j] = 1 + Math.Min(dp[1, j], Math.Min(dp[1, j + 1], dp[0, j + 1]));
            }

            for (int j = 0; j <= n2; ++j) {
                dp[1, j] = dp[0, j];
            }
        }

        return dp[1, 0];
    }
}