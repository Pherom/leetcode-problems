class Solution {
public:
    int minSteps(string const& s, string const& t) {
        size_t size = s.size();
        array<int, 26> freq{0};

        int count = 0;

        for (int i = 0; i < size; ++i) {
            ++freq[t[i] - 'a'];
        }

        for (int i = 0; i < size; ++i) {
            if (freq[s[i] - 'a'] == 0) {
                ++count;
            } else {
                --freq[s[i] - 'a'];
            }
        }

        return count;
    }
};