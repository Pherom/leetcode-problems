int maxProfit(int* prices, int pricesSize) {
    int buy = prices[0];
    int profit = 0;

    for (int i = 1; i < pricesSize; ++i) {
        int potentialProfit = prices[i] - buy;

        if (potentialProfit > profit) {
            profit = potentialProfit;
        } else if (prices[i] < buy) {
            buy = prices[i];
        }
    }

    return profit;
}