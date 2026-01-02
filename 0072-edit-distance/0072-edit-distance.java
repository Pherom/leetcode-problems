class Solution {
    public int minDistance(String word1, String word2) {
        int len1 = word1.length();
        int len2 = word2.length();
        char charArr1[] = word1.toCharArray();
        char charArr2[] = word2.toCharArray();

        int dp[] = new int[len1 + 1];

        for (int j = 0; j < len1; ++j) {
            dp[j] = len1 - j;
        }

        for (int i = len2 - 1; i >= 0; --i) {
            int diag = dp[len1];
            dp[len1] = len2 - i;

            for (int j = len1 - 1; j >= 0; --j) {
                int temp = dp[j];

                if (charArr1[j] == charArr2[i]) {
                    dp[j] = diag;
                    diag = temp;
                    continue;
                }

                dp[j] = 1 + Math.min(dp[j + 1], Math.min(diag, dp[j]));
                diag = temp;
            }
        }

        return dp[0];
    }
}