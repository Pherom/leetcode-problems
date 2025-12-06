class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        vector<int>::size_type n = nums.size();
        int write = 0;
        int read = 0;

        while (write < n && nums[write] != val) {
            ++write;
            ++read;
        }

        while (read < n) {
            if (nums[read] == val) {
                ++read;
                continue;
            }

            nums[write++] = nums[read++];
        }

        return write;
    }
};