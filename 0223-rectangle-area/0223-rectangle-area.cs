public class Solution {
    public int ComputeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int areaA = (ax2 - ax1) * (ay2 - ay1);
        int areaB = (bx2 - bx1) * (by2 - by1);
        int widthIntersection = Math.Min(ax2, bx2) - Math.Max(ax1, bx1);
        int heightIntersection = Math.Min(ay2, by2) - Math.Max(ay1, by1);
        int result = areaA + areaB;

        if (widthIntersection > 0 && heightIntersection > 0) {
            result -= widthIntersection * heightIntersection;
        }

        return result;
    }
}