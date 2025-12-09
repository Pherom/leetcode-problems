public class Solution {
    public int Reverse(int x) {
        if (x == Int32.MinValue || x == Int32.MaxValue) {
            return 0;
        }

        int result = 0;
        bool isNeg = x < 0;
        x = Math.Abs(x);

        while (x > 0) {
            int dig = x % 10;
            x /= 10;

            if (result > Int32.MaxValue / 10) {
                return 0;
            }

            result *= 10;

            if (result + dig < result) {
                return 0;
            }

            result += dig;
        }

        if (isNeg) {
            result *= -1;
        }

        return result;
    }
}