int removeElement(int* nums, int numsSize, int val) {
    int read = 0;
    int write = 0;

    while (write < numsSize && nums[write] != val) {
        ++write;
        ++read;
    }

    while (read < numsSize) {
        int curr = nums[read];

        if (curr != val) {
            nums[write++] = curr;
        }

        ++read;
    }

    return write;
}