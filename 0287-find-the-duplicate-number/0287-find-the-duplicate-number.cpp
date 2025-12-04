class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int res = 0;
        vector<int>::size_type n = nums.size();

        for (int num : nums) {
            int absolute = abs(num);

            if (nums[absolute] < 0) {
                res = absolute;
                break;
            }

            nums[absolute] = -1 * nums[absolute];
        }

        for (int i = 0; i < n; ++i) {
            nums[i] = abs(nums[i]);
        }

        return res;
    }
};