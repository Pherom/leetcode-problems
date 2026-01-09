class Solution {
public:
    int maxArea(vector<int>& height) {
        vector<int>::size_type left = 0;
        vector<int>::size_type right = height.size() - 1;
        unsigned long long res = 0;

        while (left < right) {
            int heightLeft = height[left];
            int heightRight = height[right];
            unsigned long long area = std::min(heightLeft, heightRight) * (right - left);
            res = std::max(area, res);

            if (heightLeft < heightRight) {
                ++left;
            } else {
                --right;
            }
        }

        return res;
    }
};