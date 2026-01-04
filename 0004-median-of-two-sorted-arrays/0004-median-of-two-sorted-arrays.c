#define MAX(first, second) ( ( ( first ) > ( second ) ) ? ( first ) : ( second ) )
#define MIN(first, second) ( ( ( first ) < ( second ) ) ? ( first ) : ( second ) )

double findMedianSortedArrays(int* nums1, int n1, int* nums2, int n2) {
    if (n2 == 0) {
        return n1 % 2 == 0 ? (nums1[n1 / 2] + nums1[n1 / 2 - 1]) / 2.0 : nums1[n1 / 2];
    }

    if (n1 == 0) {
        return n2 % 2 == 0 ? (nums2[n2 / 2] + nums2[n2 / 2 - 1]) / 2.0 : nums2[n2 / 2];
    }

    if (n1 < n2) {
        return findMedianSortedArrays(nums2, n2, nums1, n1);
    }

    int n = n1 + n2;
    int half = (n + 1) / 2;
    int left2 = 0;
    int right2 = n2;

    while (left2 <= right2) {
        int mid2 = (left2 + right2) / 2;
        int mid1 = half - mid2;

        int l1 = mid1 <= 0 ? INT32_MIN : nums1[mid1 - 1];
        int l2 = mid2 <= 0 ? INT32_MIN : nums2[mid2 - 1];
        int r1 = mid1 >= n1 ? INT32_MAX : nums1[mid1];
        int r2 = mid2 >= n2 ? INT32_MAX : nums2[mid2];

        if (l1 <= r2 && l2 <= r1) {
            return n % 2 == 0 ? (MAX(l1, l2) + MIN(r1, r2)) / 2.0 : MAX(l1, l2);
        } else if (l1 > r2) {
            left2 = mid2 + 1;
        } else {
            right2 = mid2 - 1;
        }
    }

    return -1;
}