#define RESULT_INIT_CAPACITY 5

static void backtrack(char*** res, int* resCapacity, int* resSize, char* curr, size_t* currSize, char* s, char** wordDict, int wordDictSize) {
    if (*s == '\0') {
        if (*resSize == *resCapacity) {
            int newCapacity = 2 * *resCapacity;
            char** temp = realloc(*res, sizeof(char*) * newCapacity);

            if (temp == NULL) {
                return; // Major issue :(
            }

            *resCapacity = newCapacity;
            *res = temp;
        }

        (*res)[*resSize] = (char*)malloc(sizeof(char) * (*currSize));

        if ((*res)[*resSize] == NULL) {
            return; // Not good! :(
        }

        strncpy((*res)[*resSize], curr, *currSize);
        (*res)[*resSize][*currSize - 1] = '\0';
        ++*resSize;
        return;
    }

    for (int i = 0; i < wordDictSize; ++i) {
        int j = 0;
        bool okWord = true;

        for (char* p = wordDict[i]; *p != '\0'; ++p) {
            if (*p != s[j]) {
                okWord = false;
                break;
            }

            ++j;
        }

        if (okWord) {
            strcpy(curr + *currSize, wordDict[i]);
            *currSize += j;
            curr[*currSize] = ' ';
            ++*currSize;
            backtrack(res, resCapacity, resSize, curr, currSize, s + j, wordDict, wordDictSize);
            *currSize -= j + 1;
        }
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** wordBreak(char* s, char** wordDict, int wordDictSize, int* returnSize) {
    size_t sLen = strlen(s);
    int capacity = RESULT_INIT_CAPACITY;
    char** res = (char**)malloc(sizeof(char*) * capacity);

    if (res == NULL) {
        return NULL;
    }

    char* curr = (char*)malloc(sizeof(char) * sLen * 2);

    if (curr == NULL) {
        free(res);
        return NULL;
    }

    size_t currSize = 0;
    *returnSize = 0;

    backtrack(&res, &capacity, returnSize, curr, &currSize, s, wordDict, wordDictSize);

    free(curr);
    return res;
}