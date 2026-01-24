int maxProfit(int* prices, int pricesSize) {
    int buy = INT32_MAX;
    int profit = 0;

    for (int i = 0; i < pricesSize; ++i) {
        int price = prices[i];
        int potentialProfit = price - buy;

        if (potentialProfit > profit) {
            profit = potentialProfit;
        } else if (price < buy) {
            buy = price;
        }
    }

    return profit;
}