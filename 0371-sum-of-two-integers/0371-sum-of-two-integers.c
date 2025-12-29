int getSum(int a, int b) {
    unsigned int mask = 1;
    unsigned int carry = 0;
    int res = 0;

    while (mask > 0) {
        int aBit = a & mask;
        int bBit = b & mask;
        res |= aBit ^ bBit ^ carry;
        carry = ((aBit & bBit) | (aBit & carry) | (bBit & carry)) << 1;
        mask <<= 1;
    }

    if (carry > 0) {
        res |= carry;
    }

    return res;
}