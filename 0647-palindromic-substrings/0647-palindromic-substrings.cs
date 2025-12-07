public class Solution {
    public int CountSubstrings(string s) {
        int sLen = s.Length;

        int CountPalindromesFrom(int i) {
            int count = 1;
            int j = i + 1;

            for (; j < sLen; ++j) {
                if (s[j] != s[i]) {
                    break;
                }

                ++count;
            }

            if (--i >= 0) {
                while (i >= 0 && j < sLen && s[i] == s[j]) {
                    ++count;
                    --i;
                    ++j;
                }
            }

            return count;
        }

        int result = 0;

        for (int i = 0; i < sLen; ++i) {
            result += CountPalindromesFrom(i);
        }

        return result;
    }
}