#define MIN(first, second) ( ( first ) < ( second ) ? ( first ) : ( second ) )

// int minDistanceRec(char* word1, char* curr1, char* word2, char* curr2) {
//     if (*curr1 == '\0') {
//         return strlen(curr2);
//     }

//     if (*curr2 == '\0') {
//         return strlen(curr1);
//     }

//     if (*curr1 == *curr2) {
//         return minDistanceRec(word1, curr1 + 1, word2, curr2 + 1);
//     }

//     int deleted = minDistanceRec(word1, curr1 + 1, word2, curr2);
//     int replaced = minDistanceRec(word1, curr1 + 1, word2, curr2 + 1);
//     int added = minDistanceRec(word1, curr1, word2, curr2 + 1);

//     return 1 + MIN(deleted, MIN(replaced, added));
// }

int minDistance(char* word1, char* word2) {
    // return minDistanceRec(word1, word1, word2, word2);
    size_t size1 = strlen(word1);
    size_t size2 = strlen(word2);

    int** dp = (int**)malloc(sizeof(int*) * (size1 + 1));

    if (dp == NULL) {
        return -1;
    }

    for (int i = 0; i <= size1; ++i) {
        dp[i] = (int*)malloc(sizeof(int) * (size2 + 1));

        if (dp[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(dp[j]);
            }

            free(dp);
            return -1;
        }
    }

    for (int i = 0; i <= size1; ++i) {
        dp[i][size2] = size1 - i;
    }

    for (int j = 0; j <= size2; ++j) {
        dp[size1][j] = size2 - j;
    }

    for (int i = size1 - 1; i >= 0; --i) {
        for (int j = size2 - 1; j >= 0; --j) {
            if (word1[i] == word2[j]) {
                dp[i][j] = dp[i + 1][j + 1];
                continue;
            }

            dp[i][j] = 1 + MIN(dp[i][j + 1], MIN(dp[i + 1][j + 1], dp[i + 1][j]));
        }
    }

    int result = dp[0][0];

    for (int i = 0; i < size1; ++i) {
        free(dp[i]);
    }

    free(dp);
    return result;
}