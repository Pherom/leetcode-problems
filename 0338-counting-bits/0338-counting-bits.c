/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int n, int* returnSize) {
    int* ans = (int*)malloc(sizeof(int) * (n + 1));

    if (ans == NULL) {
        return NULL;
    }

    ans[0] = 0;
    unsigned int bound = 1;

    for (int i = 1; i <= n; ++i) {
        if (i == (bound << 1)) {
            bound <<= 1;
        }

        ans[i] = 1 + ans[i - bound];
    }

    *returnSize = n + 1;
    return ans;
}