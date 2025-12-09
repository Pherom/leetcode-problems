public class Solution {
    public void Rotate(int[] nums, int k) {
        int n = nums.Length;
        k = k % n;

        Array.Reverse(nums);
        Array.Reverse(nums, 0, k);
        Array.Reverse(nums, k, n - k);
    }
}