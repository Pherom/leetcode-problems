class Solution {
private:
    void buildLut(array<unsigned char, numeric_limits<unsigned char>::max() + 1>& lut) {
        lut[0] = 0;

        unsigned char curr = 1;
        unsigned char rev = 0;

        while (curr > 0) {
            unsigned char copy = curr;

            for (int i = 0; i < CHAR_BIT; ++i) {
                rev <<= 1;

                if ((copy & 1) > 0) {
                    rev |= 1;
                }

                copy >>= 1;
            }

            lut[curr++] = rev;
        }
    }

public:
    unsigned char reverseBits(unsigned char n) {
        static array<unsigned char, numeric_limits<unsigned char>::max() + 1> lut{};
        static bool lutBuilt = false;

        if (!lutBuilt) {
            buildLut(lut);
            lutBuilt = true;
        }

        return lut[n];
    }

    int reverseBits(int n) {
        unsigned int un = static_cast<unsigned int>(n);
        unsigned int rev = 0;

        for (int i = 0; i < sizeof(int); ++i) {
            rev <<= CHAR_BIT;
            rev |= reverseBits(static_cast<unsigned char>(un));
            un >>= CHAR_BIT;
        }

        return rev;
    }
};