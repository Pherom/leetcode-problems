int rangeBitwiseAnd(int left, int right) {
    unsigned int uleft = left;
    unsigned int uright = right;
    unsigned int result = 0;
    unsigned int mask = 1;

    while (uleft > 0 || uright > 0) {
        if (uleft & 1 > 0 && uright - uleft < 1) {
            result |= mask;
        }

        mask <<= 1;
        uright >>= 1;
        uleft >>= 1;
    }

    return result;
}