public class Solution {
    private static byte[] lut;

    static Solution() {
        lut = new byte[1 << 8];
        buildLUT();
    }

    private static void buildLUT() {
        lut[0] = 0;

        byte curr = 1;

        while (curr > 0) {
            byte num = curr;
            byte count = 0;

            while (num > 0) {
                count += (byte)(num & 1);
                num >>= 1;
            }

            lut[curr] = count;
            ++curr;
        }
    }

    public int HammingWeight(int n) {
        uint un = (uint)n;
        int count = 0;

        while (un > 0) {
            count += lut[(byte)un];
            un >>= 8;
        }

        return count;
    }
}