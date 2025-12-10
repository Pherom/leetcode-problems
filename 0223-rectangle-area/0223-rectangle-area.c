#include <math.h>

#define MIN(a, b) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define MAX(a, b) ( ( a ) < ( b ) ? ( b ) : ( a ) )

int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    int area = abs(ax2 - ax1) * abs(ay2 - ay1) + abs(bx2 - bx1) * abs(by2 - by1);

    area -= MAX(0, MIN(ax2, bx2) - MAX(ax1, bx1)) * MAX(0, MIN(ay2, by2) - MAX(ay1, by1));

    return area;
}