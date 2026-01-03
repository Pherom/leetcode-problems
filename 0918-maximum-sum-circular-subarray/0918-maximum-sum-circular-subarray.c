#define MAX(first, second) ( ( first ) > ( second ) ? ( first ) : ( second ) )
#define MIN(first, second) ( ( first ) < ( second ) ? ( first ) : ( second ) )

int maxSubarraySumCircular(int* nums, int numsSize) {
    long long globalMax = nums[0];
    long long globalMin = nums[0];
    long long max = 0;
    long long min = 0;
    long long total = 0;

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        long long includedMax = max + num;
        long long includedMin = min + num;

        max = MAX(num, includedMax);
        min = MIN(num, includedMin);

        globalMax = MAX(globalMax, max);
        globalMin = MIN(globalMin, min);

        total += num;
    }

    if (globalMin == total) {
        return globalMax;
    }

    long long altMax = total - globalMin;
    return MAX(globalMax, altMax);
}