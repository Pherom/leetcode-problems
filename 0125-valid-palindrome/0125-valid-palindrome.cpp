class Solution {
public:
    bool isPalindrome(string const& s) {
        size_t n = s.size();

        if (n == 0) {
            return true;
        }

        size_t left = 0;
        size_t right = n - 1;

        while (left < right) {
            char cl = tolower(s[left]);
            char cr = tolower(s[right]);

            if (!isalnum(cl)) {
                ++left;
                continue;
            }

            if (!isalnum(cr)) {
                --right;
                continue;
            }

            if (cl != cr) {
                return false;
            }

            ++left;
            --right;
        }

        return true;
    }
};