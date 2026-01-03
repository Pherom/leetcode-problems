class Solution {
public:
    vector<int> countBits(int n) {
        unsigned int bound = 1;
        vector<int> result(n + 1);
        result[0] = 0;

        for (int i = 1; i <= n; ++i) {
            if (i == bound << 1) {
                bound <<= 1;
            }

            result[i] = 1 + result[i - bound];
        }

        return result;
    }
};