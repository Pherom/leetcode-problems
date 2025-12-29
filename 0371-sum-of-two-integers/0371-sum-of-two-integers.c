int getSum(int a, int b) {
    unsigned int ua = a;
    unsigned int ub = b;
    unsigned int carry = 0;
    unsigned int res = 0;
    unsigned int mask = 1;

    while (mask > 0) {
        unsigned int aBit = ua & mask;
        unsigned int bBit = ub & mask;
        unsigned int resBit = aBit ^ bBit ^ carry;
        carry = ((aBit & bBit) | (aBit & carry) | (bBit & carry)) << 1;
        res |= resBit;
        mask <<= 1;
    }

    if (carry > 0) {
        res |= carry;
    }

    return res;
}