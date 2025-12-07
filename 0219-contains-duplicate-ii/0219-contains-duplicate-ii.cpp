class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        int m = min(k + 1, n);
        unordered_set<int> numsInRange{};

        int left = 0;
        int right = 0;

        while (right - left < m) {
            if (numsInRange.find(nums[right]) != numsInRange.end()) {
                return true;
            }

            numsInRange.insert(nums[right++]);
        }

        while (right < n) {
            auto it = numsInRange.find(nums[left++]);
            numsInRange.erase(it);

            if (numsInRange.find(nums[right]) != numsInRange.end()) {
                return true;
            }

            numsInRange.insert(nums[right++]);
        }

        return false;
    }
};