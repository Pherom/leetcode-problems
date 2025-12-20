#define DIR_COUNT 4

#define MAX(first, second) ( ( first ) > ( second ) ? ( first ) : ( second ) )

static const int dirs[DIR_COUNT][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

int getIslandArea(int** grid, int m, int n, int i, int j) {
    grid[i][j] = 2;
    int count = 1;

    for (int k = 0; k < DIR_COUNT; ++k) {
        int ni = i + dirs[k][0];
        int nj = j + dirs[k][1];

        if (ni < 0 || ni >= m || nj < 0 || nj >= n || grid[ni][nj] != 1) {
            continue;
        }

        count += getIslandArea(grid, m, n, ni, nj);
    }

    return count;
}

int maxAreaOfIsland(int** grid, int m, int* nPtr) {
    int n = *nPtr;
    int result = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                int area = getIslandArea(grid, m, n, i, j);
                result = MAX(result, area);
            }
        }
    }

    return result;
}