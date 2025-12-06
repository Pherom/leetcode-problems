class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int>::size_type n = nums.size();

        if (n <= 1) {
            return n;
        }

        int write = 1;
        int read = 1;

        while (write < n && nums[write] != nums[write - 1]) {
            ++write;
            ++read;
        }

        while (read < n) {
            if (nums[read] != nums[read - 1]) {
                nums[write++] = nums[read];
            }

            ++read;
        }

        return write;
    }
};