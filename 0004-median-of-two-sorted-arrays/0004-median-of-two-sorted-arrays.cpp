class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>::size_type n1 = nums1.size();
        vector<int>::size_type n2 = nums2.size();

        if (n2 > n1) {
            return findMedianSortedArrays(nums2, nums1);
        }

        if (n1 == 0) {
            return n2 % 2 == 0 ? (nums2[n2 / 2] + nums2[n2 / 2 - 1]) / 2.0 : nums2[n2 / 2];
        }

        if (n2 == 0) {
            return n1 % 2 == 0 ? (nums1[n1 / 2] + nums1[n1 / 2 - 1]) / 2.0 : nums1[n1 / 2];
        }

        vector<int>::size_type n = n1 + n2;
        vector<int>::size_type half = (n + 1) / 2;

        int left2 = 0;
        int right2 = n2;

        while (left2 <= right2) {
            int mid2 = (left2 + right2) / 2;
            int mid1 = half - mid2;

            int l1 = mid1 > 0 ? nums1[mid1 - 1] : numeric_limits<int>::min();
            int r1 = mid1 < n1 ? nums1[mid1] : numeric_limits<int>::max();
            int l2 = mid2 > 0 ? nums2[mid2 - 1] : numeric_limits<int>::min();
            int r2 = mid2 < n2 ? nums2[mid2] : numeric_limits<int>::max();

            if (l1 <= r2 && l2 <= r1) {
                return n % 2 == 0 ? (max(l1, l2) + min(r1, r2)) / 2.0 : max(l1, l2);
            }

            if (l1 > r2) {
                left2 = mid2 + 1;
            } else {
                right2 = mid2 - 1;
            }
        }

        return 0;
    }
};