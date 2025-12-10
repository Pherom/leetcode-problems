public class Solution {
    public int RemoveDuplicates(int[] nums) {
        int n = nums.Length;
        int read = 1;
        int write = 1;

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
}