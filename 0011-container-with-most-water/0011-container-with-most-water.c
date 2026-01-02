#define MIN(first, second) ( ( first ) < ( second ) ? ( first ) : ( second ) );

int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int result = 0;

    while (left < right) {
        int heightLeft = height[left];
        int heightRight = height[right];

        int curr = (right - left) * MIN(heightLeft, heightRight);

        if (curr > result) {
            result = curr;
        }

        if (heightLeft > heightRight) {
            --right;
        } else if (heightRight > heightLeft) {
            ++left;
        } else {
            --right;
            ++left;
        }
    }

    return result;
}