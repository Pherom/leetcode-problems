int majorityElement(int* nums, int numsSize) {
    int result = nums[0];
    int count = 1;

    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] == result) {
            ++count;
        } else {
            if (count == 0) {
                result = nums[i];
            } else {
                --count;
            }
        }
    }

    return result;
}