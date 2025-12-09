public class Solution {
    public IList<IList<int>> FourSum(int[] nums, int target) {
        int n = nums.Length;
        var res = new List<List<int>>(n);
        Array.Sort(nums);
        long targetLong = target;

        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            targetLong -= nums[i];

            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }

                targetLong -= nums[j];

                int left = j + 1;
                int right = n - 1;

                while (left < right) {
                    long sum = nums[left] + nums[right];

                    if (sum == targetLong) {
                        res.Add(new List<int>(4){ nums[i], nums[j], nums[left], nums[right] });

                        do {
                            ++left;
                        } while (left < right && nums[left] == nums[left - 1]);

                        do {
                            --right;
                        } while (left < right && nums[right] == nums[right + 1]);
                    } else if (sum < targetLong) {
                        ++left;
                    } else {
                        --right;
                    }
                }

                targetLong += nums[j];
            }

            targetLong += nums[i];
        }

        return res.ToArray();
    }
}