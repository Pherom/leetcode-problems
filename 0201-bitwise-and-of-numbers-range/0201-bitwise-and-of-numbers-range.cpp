class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int res = 0;
        unsigned int uleft = left;
        unsigned int uright = right;
        unsigned int mask = 1;

        while (uleft > 0 || uright > 0) {
            if ((uleft & 1) > 0 && uright == uleft) {
                res |= mask;
            }

            mask <<= 1;
            uright >>= 1;
            uleft >>= 1;
        }

        return res;
    }
};