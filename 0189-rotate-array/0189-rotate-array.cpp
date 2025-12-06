class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int>::size_type n = nums.size();
        k = k % n;

        if (k == 0) {
            return;
        }

        int left = 0;
        int right = n - 1;

        while (left < right) {
            std::swap(nums[left++], nums[right--]);
        }

        std::reverse(nums.begin(), std::next(nums.begin(), k));
        std::reverse(std::next(nums.begin(), k), nums.end());
    }
};