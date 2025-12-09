public class Solution {
    private static void kSum(List<List<int>> res, int[] curr, int[] nums, int n, long target, int k, int start, int addedCount) {
        if (k == 2) {
            int left = start;
            int right = n - 1;

            while (left < right) {
                long sum = nums[left] + nums[right];

                if (sum == target) {
                    curr[addedCount] = nums[left];
                    curr[addedCount + 1] = nums[right];
                    res.Add(new List<int>(curr));

                    do {
                        ++left;
                    } while (left < right && nums[left] == nums[left - 1]);

                    do {
                        --right;
                    } while (left < right && nums[right] == nums[right + 1]);
                } else if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }

            return;
        }

        for (int i = start; i < n - k + 1; ++i) {
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }

            curr[addedCount++] = nums[i];
            kSum(res, curr, nums, n, target - nums[i], k - 1, i + 1, addedCount);
            --addedCount;
        }
    }

    public IList<IList<int>> FourSum(int[] nums, int target) {
        int n = nums.Length;
        var res = new List<List<int>>(n);
        int[] curr = new int[4];
        Array.Sort(nums);

        kSum(res, curr, nums, n, target, 4, 0, 0);
        return res.ToArray();
    }
}