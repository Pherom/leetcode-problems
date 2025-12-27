


typedef struct {
    long long* sumMat;
    int m;
    int n;
} NumMatrix;


NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrix == NULL || matrixColSize == NULL) {
        return NULL;
    }

    long long* sumMat = (long long*)malloc(sizeof(long long) * matrixSize * *matrixColSize);

    if (sumMat == NULL) {
        return NULL;
    }

    NumMatrix* result = (NumMatrix*)malloc(sizeof(NumMatrix));

    if (result == NULL) {
        free(sumMat);
        return NULL;
    }

    int m = matrixSize;
    int n = *matrixColSize;

    sumMat[0] = matrix[0][0];

    for (int j = 1; j < n; ++j) {
        sumMat[j] = sumMat[j - 1] + matrix[0][j];
    }

    for (int i = 1; i < m; ++i) {
        sumMat[i * n] = sumMat[(i - 1) * n] + matrix[i][0];
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            sumMat[i * n + j] = sumMat[(i - 1) * n + j] + sumMat[i * n + j - 1] - sumMat[(i - 1) * n + j - 1] + matrix[i][j];
        }
    }

    result->sumMat = sumMat;
    result->m = m;
    result->n = n;
    return result;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    if (obj == NULL || row1 > row2 || col1 > col2 || row1 < 0 || col1 < 0 || row2 >= obj->m || col2 >= obj->n) {
        return -1;
    }

    long long top = 0;
    long long left = 0;
    long long diag = 0;
    long long* sumMat = obj->sumMat;
    int m = obj->m;
    int n = obj->n;

    if (row1 > 0) {
        top = sumMat[(row1 - 1) * n + col2];
    }

    if (col1 > 0) {
        left = sumMat[row2 * n + col1 - 1];
    }

    if (row1 > 0 && col1 > 0) {
        diag = sumMat[(row1 - 1) * n + col1 - 1];
    }

    return sumMat[row2 * n + col2] - top - left + diag;
}

void numMatrixFree(NumMatrix* obj) {
    if (obj == NULL) {
        return;
    }

    free(obj->sumMat);
    free(obj);
}

/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);
 
 * numMatrixFree(obj);
*/