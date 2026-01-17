public class Solution {
    public string AddBinary(string a, string b) {
        if (b.Length > a.Length) {
            return AddBinary(b, a);
        }

        char[] resArr = new char[a.Length + 1];
        resArr[a.Length] = '\0';

        int carry = 0;
        int bI = b.Length - 1;
        int aI = a.Length - 1;
        int resI = 0;

        while (aI >= 0 && bI >= 0) {
            int aBit = a[aI--] - '0';
            int bBit = b[bI--] - '0';

            int resBit = aBit ^ bBit ^ carry;
            carry = (aBit & bBit) | (aBit & carry) | (bBit & carry);

            resArr[resI++] = (char)('0' + resBit);
        }

        while (aI >= 0) {
            int aBit = a[aI--] - '0';

            int resBit = aBit ^ carry;
            carry = aBit & carry;

            resArr[resI++] = (char)('0' + resBit);
        }

        while (bI >= 0) {
            int bBit = b[bI--] - '0';

            int resBit = bBit ^ carry;
            carry = bBit & carry;

            resArr[resI++] = (char)('0' + resBit);
        }

        if (carry > 0) {
            resArr[resI] = '1';
        } else {
            Array.Resize(ref resArr, resArr.Length - 1);
        }

        Array.Reverse(resArr);
        return new string(resArr);
    }
}