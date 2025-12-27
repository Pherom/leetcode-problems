int maxProfit(int* prices, int pricesSize) {
    if (prices == NULL || pricesSize <= 0) {
        return 0;
    }

    int buy = prices[0];
    int profit = 0;

    for (int i = 1; i < pricesSize; ++i) {
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