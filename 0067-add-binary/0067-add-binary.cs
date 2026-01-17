public class Solution {
    private void handleRemaining(string a, ref int aI, char[] resArr, ref int resI, ref int carry) {
        while (aI >= 0) {
            int aBit = a[aI--] - '0';

            int resBit = aBit ^ carry;
            carry = aBit & carry;

            resArr[resI++] = (char)('0' + resBit);
        }
    }

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

        handleRemaining(a, ref aI, resArr, ref resI, ref carry);
        handleRemaining(b, ref bI, resArr, ref resI, ref carry);

        if (carry > 0) {
            resArr[resI] = '1';
        } else {
            Array.Resize(ref resArr, resArr.Length - 1);
        }

        Array.Reverse(resArr);
        return new string(resArr);
    }
}