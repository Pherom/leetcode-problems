/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define STRS_MAX_LENGTH 10000
#define ALPHABET_SIZE 26
#define RES_INIT_CAPACITY 20

static void initCounters(int counters[][ALPHABET_SIZE], char** strs, int strsSize) {
    for (int i = 0; i < strsSize; ++i) {
        for (char* p = strs[i]; *p != '\0'; ++p) {
            ++counters[i][*p - 'a'];
        }
    }
}

static void cleanupRes(char*** res, int size) {
    for (int i = 0; i < size; ++i) {
        free(res[i]);
    }

    free(res);
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    int capacity = RES_INIT_CAPACITY;
    char*** res = (char***)malloc(sizeof(char**) * capacity);

    if (res == NULL) {
        return NULL;
    }

    *returnSize = 0;

    *returnColumnSizes = (int*)malloc(sizeof(int) * capacity);

    if (*returnColumnSizes == NULL) {
        free(res);
        return NULL;
    }

    bool* visited = (bool*)calloc(strsSize, sizeof(bool));

    if (visited == NULL) {
        free(*returnColumnSizes);
        free(res);
        return NULL;
    }

    int counters[STRS_MAX_LENGTH][ALPHABET_SIZE] = {0};
    initCounters(counters, strs, strsSize);

    for (int i = 0; i < strsSize; ++i) {
        if (visited[i]) {
            continue;
        }

        if (*returnSize == capacity) {
            int newCapacity = capacity * 2;
            char*** tempRes = (char***)realloc(res, newCapacity * sizeof(char**));
            int* tempColSizes = (int*)realloc(*returnColumnSizes, newCapacity * sizeof(int));

            if (tempRes == NULL || tempColSizes == NULL) {
                cleanupRes(res, *returnSize);
                free(visited);
                free(*returnColumnSizes);
                return NULL;
            }

            res = tempRes;
            *returnColumnSizes = tempColSizes;
            capacity = newCapacity;
        }

        res[*returnSize] = (char**)malloc(sizeof(char*) * strsSize);

        if (res[*returnSize] == NULL) {
            cleanupRes(res, *returnSize);
            free(visited);
            free(*returnColumnSizes);
            return NULL;
        }

        res[*returnSize][0] = strs[i];
        (*returnColumnSizes)[*returnSize] = 1;
        visited[i] = true;

        for (int j = i + 1; j < strsSize; ++j) {
            if (visited[j]) {
                continue;
            }

            bool anagram = true;

            for (int k = 0; k < ALPHABET_SIZE; ++k) {
                if (counters[i][k] != counters[j][k]) {
                    anagram = false;
                    break;
                }
            }

            if (anagram) {
                res[*returnSize][(*returnColumnSizes)[*returnSize]++] = strs[j];
                visited[j] = true;
            }
        }

        ++*returnSize;
    }

    free(visited);
    return res;
}