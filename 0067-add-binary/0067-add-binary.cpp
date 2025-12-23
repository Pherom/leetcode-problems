class Solution {
public:
    string addBinary(string a, string b) {
        size_t aLen = a.size();
        size_t bLen = b.size();
        string result{};
        result.reserve(std::max(aLen, bLen) + 1);

        size_t aI = aLen;
        size_t bI = bLen;
        unsigned char carry = 0;

        while (aI > 0 && bI > 0) {
            --aI;
            --bI;

            unsigned char aBit = a[aI] - '0';
            unsigned char bBit = b[bI] - '0';

            unsigned char resBit = aBit ^ bBit ^ carry;
            carry = (aBit & bBit) | (aBit & carry) | (bBit & carry);

            result.push_back(resBit + '0');
        }

        while (aI --> 0) {
            unsigned char aBit = a[aI] - '0';

            unsigned char resBit = aBit ^ carry;
            carry = aBit & carry;

            result.push_back(resBit + '0');
        }

        while (bI --> 0) {
            unsigned char bBit = b[bI] - '0';

            unsigned char resBit = bBit ^ carry;
            carry = bBit & carry;

            result.push_back(resBit + '0');
        }

        if (carry > 0) {
            result.push_back(carry + '0');
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};