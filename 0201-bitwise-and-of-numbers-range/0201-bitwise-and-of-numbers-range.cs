public class Solution {
    public int RangeBitwiseAnd(int left, int right) {
        uint uleft = (uint)left;
        uint uright = (uint)right;
        int res = 0;
        int mask = 1;

        while (uleft > 0) {
            if (uleft % 2 == 1 && uright == uleft) {
                res |= mask;
            }

            uright >>= 1;
            uleft >>= 1;
            mask <<= 1;
        }

        return res;
    }
}