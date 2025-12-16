/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
static void buildLUT(unsigned char* lut) {
    lut[0] = 0;

    unsigned char curr = 1;

    while (curr > 0) {
        unsigned char copy = curr;

        while (copy > 0) {
            if ((copy & 1) > 0) {
                ++lut[curr];
            }

            copy >>= 1;
        }

        ++curr;
    }
}

static unsigned char countBitsByte(unsigned char byte) {
    static unsigned char lut[1 << CHAR_BIT];
    static bool lutBuilt = false;

    if (!lutBuilt) {
        buildLUT(lut);
        lutBuilt = true;
    }

    return lut[byte];
}

int* countBits(int n, int* returnSize) {
    if (returnSize == NULL) {
        return NULL;
    }

    int* result = (int*)calloc(n + 1, sizeof(int));

    if (result == NULL) {
        return NULL;
    }

    *returnSize = n + 1;

    result[0] = 0;
    for (int i = 1; i <= n; ++i) {
        unsigned int copy = i;

        while (copy > 0) {
            result[i] += countBitsByte(copy);
            copy >>= CHAR_BIT;
        }
    }

    return result;
}