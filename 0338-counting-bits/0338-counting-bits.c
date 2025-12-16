/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_N 100000

int result[MAX_N + 1] = {0};

int* countBits(int n, int* returnSize) {
    if (returnSize == NULL) {
        return NULL;
    }

    *returnSize = n + 1;

    memset(result, 0, *returnSize * sizeof(int));

    result[0] = 0;
    for (int i = 1; i <= n; ++i) {
        unsigned int copy = i;

        while (copy > 0) {
            if ((copy & 1) > 0) {
                ++result[i];
            }

            copy >>= 1;
        }
    }

    return result;
}