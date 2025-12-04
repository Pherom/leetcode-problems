class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>::size_type n1 = nums1.size();
        vector<int>::size_type n2 = nums2.size();

        if (n1 == 0) {
            return n2 % 2 == 0 ? (nums2[n2 / 2] + nums2[n2 / 2 - 1]) / 2.0 : nums2[n2 / 2];
        }

        if (n2 == 0) {
            return n1 % 2 == 0 ? (nums1[n1 / 2] + nums1[n1 / 2 - 1]) / 2.0 : nums1[n1 / 2];
        }

        // Make sure nums1 always has the most elements
        if (n2 > n1) {
            return findMedianSortedArrays(nums2, nums1);
        }

        vector<int>::size_type n = n1 + n2;
        vector<int>::size_type half = (n + 1) / 2; // The size of the left portion in the merged array

        int left2 = 0;
        int right2 = n2;
        
        while (left2 <= right2) {
            // mid2 represents the size of the left partition of the merged array in nums2
            int mid2 = (left2 + right2) / 2;
            // mid1 reperesents the same but for nums1 (so the rest)
            int mid1 = half - mid2;

            int l1 = mid1 - 1 < 0 ? numeric_limits<int>::min() : nums1[mid1 - 1];
            int l2 = mid2 - 1 < 0 ? numeric_limits<int>::min() : nums2[mid2 - 1];
            int r1 = mid1 >= n1 ? numeric_limits<int>::max() : nums1[mid1];
            int r2 = mid2 >= n2 ? numeric_limits<int>::max() : nums2[mid2];

            if (l1 <= r2 && l2 <= r1) {
                return n % 2 == 0 ? (max(l1, l2) + min(r1, r2)) / 2.0 : max(l1, l2);
            }

            if (l1 > r2) {
                // There are still items to take from nums2
                left2 = mid2 + 1;
            } else {
                // There are too many items taken from nums2
                right2 = mid2 - 1;
            }
        }

        return 0;
    }
};