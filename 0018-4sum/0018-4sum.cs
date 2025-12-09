public class Solution {
    public IList<IList<int>> FourSum(int[] nums, int target) {
        int n = nums.Length;
        IList<IList<int>> res = new List<IList<int>>();
        List<int> curr = new List<int>();
        Array.Sort(nums);

        void kSum(long target, int k, int start) {
            if (k == 2) {
                int left = start;
                int right = n - 1;

                while (left < right) {
                    long sum = nums[left] + nums[right];

                    if (sum == target) {
                        curr.Add(nums[left]);
                        curr.Add(nums[right]);
                        res.Add(new List<int>(curr));
                        curr.RemoveRange(curr.Count - 2, 2);

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

                curr.Add(nums[i]);
                kSum(target - nums[i], k - 1, i + 1);
                curr.RemoveAt(curr.Count - 1);
            }
        }

        kSum(target, 4, 0);
        return res;
    }
}