int reverseBits(int n) {
    int result = 0;

    for (int i = 0; i < sizeof(int) * CHAR_BIT; ++i) {
        result <<= 1;

        unsigned int bit = n & 1;

        if (bit > 0) {
            result |= 1;
        }

        n >>= 1;
    }

    return result;
}