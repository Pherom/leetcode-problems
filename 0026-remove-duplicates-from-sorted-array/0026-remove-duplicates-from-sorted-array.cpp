class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int>::size_type n = nums.size();

        int write = 1;
        int read = 1;

        while (read < n) {
            if (nums[read] == nums[read - 1]) {
                ++read;
                continue;
            }

            nums[write++] = nums[read++];
        }

        return write;
    }
};