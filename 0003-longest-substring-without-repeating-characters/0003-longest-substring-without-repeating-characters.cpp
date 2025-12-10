class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        size_t n = s.size();

        if (n <= 1) {
            return n;
        }

        array<bool, numeric_limits<unsigned char>::max() + 1> charsInCurr{ false };
        charsInCurr[static_cast<unsigned char>(s[0])] = true;

        size_t left = 0;
        size_t right = 1;
        size_t longest = 1;

        while (right < n) {
            unsigned char contender = static_cast<unsigned char>(s[right]);

            if (!charsInCurr[contender]) {
                charsInCurr[contender] = true;
                ++right;
                longest = std::max(longest, right - left);
            } else {
                while (s[left] != contender) {
                    unsigned char leftChar = static_cast<unsigned char>(s[left]);

                    if (charsInCurr[leftChar]) {
                        charsInCurr[leftChar] = false;
                    }

                    ++left;
                }

                ++left;
                ++right;
            }
        }

        longest = std::max(longest, right - left);
        return longest;
    }
};