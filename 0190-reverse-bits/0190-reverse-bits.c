static void buildLUT(unsigned char* lut) {
    lut[0] = 0;

    unsigned char curr = 1;

    while (curr > 0) {
        unsigned char copy = curr;
        unsigned char reversed = 0;

        for (int i = 0; i < CHAR_BIT; ++i) {
            reversed <<= 1;

            unsigned char bit = copy & 1;

            if (bit > 0) {
                reversed |= 1;
            }

            copy >>= 1;
        }

        lut[curr++] = reversed;
    }
}

static unsigned char reverseBitsByte(unsigned char n) {
    static char lut[1 << CHAR_BIT];
    static bool lutBuilt = false;

    if (!lutBuilt) {
        buildLUT(lut);
        lutBuilt = true;
    }

    return lut[n];
}

int reverseBits(int n) {
    int result = 0;

    for (int i = 0; i < sizeof(int); ++i) {
        result <<= CHAR_BIT;

        unsigned char rmBReversed = reverseBitsByte(n);

        result |= (unsigned int)rmBReversed;

        n >>= CHAR_BIT;
    }

    return result;
}