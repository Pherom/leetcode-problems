bool canJump(int* nums, int numsSize) {
    int allowed = 0;

    for (int i = 0; i < numsSize; ++i) {
        if (i > allowed) {
            return false;
        }

        int dist = i + nums[i];

        if (dist > allowed) { 
            allowed = dist;
        }
    }

    return true;
}