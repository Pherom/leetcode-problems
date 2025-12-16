/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

static int dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

static void dfs(int** image, int m, int n, int i, int j, int ogColor, int color) {
    image[i][j] = color;

    for (int k = 0; k < sizeof(dirs) / sizeof(dirs[0]); ++k) {
        int ni = i + dirs[k][0];
        int nj = j + dirs[k][1];

        if (ni < 0 || ni >= m || nj < 0 || nj >= n || image[ni][nj] != ogColor) {
            continue;
        }

        dfs(image, m, n, ni, nj, ogColor, color);
    }
}

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize, int** returnColumnSizes) {
    if (image == NULL || imageSize < 0 || imageColSize == NULL || sr < 0 || sr >= imageSize || sc < 0 || sc >= *imageColSize || returnSize == NULL || returnColumnSizes == NULL) {
        return NULL;
    }

    *returnColumnSizes = (int*)malloc(sizeof(int) * imageSize);

    if(*returnColumnSizes == NULL) {
        return NULL;
    }

    for (int i = 0; i < imageSize; ++i) {
        (*returnColumnSizes)[i] = *imageColSize;
    }

    *returnSize = imageSize;

    int ogColor = image[sr][sc];

    if (ogColor != color) {
        dfs(image, imageSize, *imageColSize, sr, sc, ogColor, color);
    }
    
    return image;
}