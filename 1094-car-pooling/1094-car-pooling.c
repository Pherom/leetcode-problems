bool carPooling(int** trips, int tripsSize, int* tripsColSize, int capacity) {
    int diff[1001] = {0};

    for (int i = 0; i < tripsSize; ++i) {
        int count = trips[i][0];
        diff[trips[i][1]] += count;
        diff[trips[i][2]] -= count;
    }

    int sum = 0;

    for (int i = 0; i <= 1000; ++i) {
        sum += diff[i];

        if (sum > capacity) {
            return false;
        }
    }

    return true;
}