class Solution {
private:
    void buildLut(std::array<unsigned char, std::numeric_limits<unsigned char>::max() + 1>& lut) {
        lut[0] = 0;

        unsigned char curr = 1;

        while (curr > 0) {
            unsigned char copy = curr;
            unsigned char count = 0;

            while (copy > 0) {
                if ((copy & 1) > 0) {
                    ++count;
                }

                copy >>= 1;
            }

            lut[curr++] = count;
        }
    }

public:
    unsigned char hammingWeight(unsigned char n) {
        static std::array<unsigned char, std::numeric_limits<unsigned char>::max() + 1> lut{};
        static bool lutBuilt = false;

        if (!lutBuilt) {
            buildLut(lut);
            lutBuilt = true;
        }

        return lut[n];
    }

    int hammingWeight(int n) {
        int count = 0;
        unsigned int un = static_cast<unsigned int>(n);

        for (int i = 0; i < sizeof(int); ++i) {
            count += hammingWeight(static_cast<unsigned char>(un));
            un >>= CHAR_BIT;
        }

        return count;
    }
};