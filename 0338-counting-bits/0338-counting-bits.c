/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    if (returnSize == NULL) {
        return NULL;
    }

    int* result = calloc(n + 1, sizeof(int));;

    if (result == NULL) {
        return NULL;
    }

    *returnSize = n + 1;
    unsigned int bound = 1;

    result[0] = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == (bound << 1)) {
            bound <<= 1;
            result[i] = 1;
        } else {
            result[i] = 1 + result[i - bound];
        }
    }

    return result;
}