void buildLUT(unsigned char* lut) {
    for (unsigned char curr = 1; curr > 0; ++curr) {
        int copy = curr;

        while (copy > 0) {
            if (copy & 1 > 0) {
                ++lut[curr];
            }

            copy >>= 1;
        }
    }
}

unsigned char hammingWeightByte(unsigned char n) {
    static unsigned char lut[1 << CHAR_BIT];
    static bool builtLUT = false;

    if (!builtLUT) {
        buildLUT(lut);
        builtLUT = true;
    }

    return lut[n];
}

int hammingWeight(int n) {
    int count = 0;

    for (int i = 0; i < sizeof(int); ++i) {
        count += hammingWeightByte(n);
        n >>= CHAR_BIT;
    }

    return count;
}