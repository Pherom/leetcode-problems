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

    int* dp = (int*)malloc(sizeof(int) * (size2 + 1));

    if (dp == NULL) {
        return -1;
    }

    for (int j = 0; j <= size2; ++j) {
        dp[j] = size2 - j;
    }

    for (int i = size1 - 1; i >= 0; --i) {
        int diag = dp[size2];
        dp[size2] = size1 - i;

        for (int j = size2 - 1; j >= 0; --j) {
            int temp = dp[j];

            if (word1[i] == word2[j]) {
                dp[j] = diag;
            } else {
                 dp[j] = 1 + MIN(dp[j], MIN(dp[j + 1], diag));
            }
           
            diag = temp;
        }
    }

    int result = dp[0];
    free(dp);
    return result;
}