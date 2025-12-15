/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(sizeof(int*) * *matrixColSize);

    if (result == NULL) {
        return NULL;
    }

    *returnColumnSizes = (int*)malloc(sizeof(int) * *matrixColSize);

    if (*returnColumnSizes == NULL) {
        free(result);
        return NULL;
    }

    for (int i = 0; i < *matrixColSize; ++i) {
        result[i] = (int*)malloc(sizeof(int) * matrixSize);
        (*returnColumnSizes)[i] = matrixSize;

        if (result[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(result[j]);
            }

            free(result);
            return NULL;
        }
    }

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < *matrixColSize; ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    *returnSize = *matrixColSize;
    return result;
}