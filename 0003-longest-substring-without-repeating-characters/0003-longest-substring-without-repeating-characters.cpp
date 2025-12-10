class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        size_t n = s.size();

        if (n <= 1) {
            return n;
        }

        unordered_set<char> charsInCurr{};
        charsInCurr.insert(s[0]);

        size_t left = 0;
        size_t right = 1;
        size_t longest = 1;

        while (right < n) {
            char contender = s[right];

            auto it = charsInCurr.find(contender);

            if (it == charsInCurr.end()) {
                charsInCurr.insert(contender);
                ++right;
                longest = std::max(longest, right - left);
            } else {
                while (s[left] != contender) {
                    it = charsInCurr.find(s[left]);

                    if (it != charsInCurr.end()) {
                        charsInCurr.erase(it);
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