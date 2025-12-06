class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int>::size_type n = nums.size();
        k = k % n;

        if (k == 0) {
            return;
        }
        
        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), std::next(nums.begin(), k));
        std::reverse(std::next(nums.begin(), k), nums.end());
    }
};