void buildLut(unsigned char* lut) {
    lut[0] = 0;

    unsigned char curr = 1;

    while (curr > 0) {
        unsigned char res = 0;
        unsigned char copy = curr;
        int leftShift = CHAR_BIT;

        while (copy > 0) {
            res <<= 1;
            res |= (copy & 1);
            copy >>= 1;
            --leftShift;
        }

        res <<= leftShift;
        lut[curr++] = res;
    }
}

unsigned char reverseBitsByte(unsigned char n) {
    static bool lutBuilt = false;
    static unsigned char lut[1 << CHAR_BIT];

    if (!lutBuilt) {
        buildLut(lut);
        lutBuilt = true;
    }

    return lut[n];
}

int reverseBits(int n) {
    if (n == 0) {
        return 0;
    }

    unsigned int res = 0;
    unsigned int un = n;
    int leftShift = CHAR_BIT * sizeof(unsigned int);

    while (un > 0) {
        res <<= CHAR_BIT;
        res |= reverseBitsByte(un);
        un >>= CHAR_BIT;
        leftShift -= CHAR_BIT;
    }

    res <<= leftShift;
    return res;
}