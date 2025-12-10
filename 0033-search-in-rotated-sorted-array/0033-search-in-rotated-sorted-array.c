int search(int* nums, int numsSize, int target) {
    if (nums == NULL || numsSize == 0) {
        return -1;
    }

    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[mid] < nums[left]) {
            // Right portion

            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {
            if (nums[mid] > target && target >= nums[left]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    
    return -1;
}