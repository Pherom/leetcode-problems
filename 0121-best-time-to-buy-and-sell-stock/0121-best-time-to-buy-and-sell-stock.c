int maxProfit(int* prices, int pricesSize) {
    int buy = prices[0];
    int profit = 0;

    for (int i = 1; i < pricesSize; ++i) {
        if (prices[i] - buy > profit) {
            profit = prices[i] - buy;
        } else if (prices[i] < buy) {
            buy = prices[i];
        }
    }

    return profit;
}