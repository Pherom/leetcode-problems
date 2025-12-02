class Solution {
public:
    int reverse(int x) {
        if (x == numeric_limits<int>::max() || x == numeric_limits<int>::min()) {
            return 0;
        }

        int mult = x < 0 ? -1 : 1;
        x = std::abs(x);

        int res = 0;

        while (x > 0) {
            if (res > numeric_limits<int>::max() / 10) {
                return 0;
            }

            res *= 10;

            int dig = x % 10;
            x /= 10;
            
            if (res + dig < res) {
                return 0;
            }

            res += dig;
        }

        if (mult == -1 && res == numeric_limits<int>::max()) {
            return 0;
        }

        return res * mult;
    }
};