#define SWAP(first, second, type) {         \
            type temp = *( first );         \
            *( first ) = *( second );       \
            *( second ) = temp;             \
        }

void reverse(int* nums, int size) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        SWAP(nums + left, nums + right, int);
        ++left;
        --right;
    }
}

void rotate(int* nums, int numsSize, int k) {
    k = k % numsSize;
    reverse(nums, numsSize);
    reverse(nums, k);
    reverse(nums + k, numsSize - k);
}