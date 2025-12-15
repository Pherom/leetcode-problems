class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        unsigned long areaA = (ay2 - ay1) * (ax2 - ax1);
        unsigned long areaB = (by2 - by1) * (bx2 - bx1);
        long cx = min(ax2, bx2) - max(ax1, bx1);
        long cy = min(ay2, by2) - max(ay1, by1);
        unsigned long areaC = cx < 0 || cy < 0 ? 0 : cx * cy;

        return areaA + areaB - areaC;
    }
};