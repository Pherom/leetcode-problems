/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    if (temperatures == NULL || temperaturesSize < 0 || returnSize == NULL) {
        return NULL;
    }

    int* stack = (int*)malloc(sizeof(int) * temperaturesSize);

    if (stack == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * temperaturesSize);

    if (result == NULL) {
        free(stack);
        return NULL;
    }

    int stackSize = 0;

    for (int i = temperaturesSize - 1; i >= 0; --i) {
        while (stackSize > 0 && temperatures[stack[stackSize - 1]] <= temperatures[i]) {
            --stackSize;
        }

        if (stackSize == 0) {
            result[i] = 0;
        } else {
            result[i] = stack[stackSize - 1] - i;
        }

        stack[stackSize++] = i;
    }

    free(stack);
    *returnSize = temperaturesSize;
    return result;
}