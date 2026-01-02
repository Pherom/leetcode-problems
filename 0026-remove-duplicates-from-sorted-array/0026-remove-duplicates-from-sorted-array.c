int removeDuplicates(int* nums, int numsSize) {
    int write = 1;

    while (write < numsSize && nums[write] != nums[write - 1]) {
        ++write;
    }

    int read = write;

    while (read < numsSize) {
        if (nums[read] != nums[read - 1]) {
            nums[write] = nums[read];
            ++write;
        }

        ++read;
    }

    return write;
}