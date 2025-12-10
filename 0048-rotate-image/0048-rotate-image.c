#define SWAP(a, b, type) {        \
            type temp = *( a );   \
            *( a ) = *( b );      \
            *( b ) = temp;        \
        }

#define REVERSE(arr, arrSize, type) {                               \
            int left = 0;                                           \
            int right = ( arrSize ) - 1;                            \
                                                                    \
            while (left < right) {                                  \
                SWAP(( arr ) + left, ( arr ) + right, type);        \
                ++left;                                             \
                --right;                                            \
            }                                                       \
        }

void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrix == NULL || matrixColSize == NULL) {
        return;
    }

    for (int i = 0; i < matrixSize; ++i) {
        if (matrix[i] == NULL) {
            return;
        }
    }

    // Transpose
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = i + 1; j < matrixSize; ++j) {
            SWAP(matrix[i] + j, matrix[j] + i, int);
        }
    }

    // Reverse Rows
    for (int i = 0; i < matrixSize; ++i) {
        REVERSE(matrix[i], matrixSize, int);
    }

    *matrixColSize = matrixSize;
}