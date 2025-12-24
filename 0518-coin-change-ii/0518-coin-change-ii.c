int change(int amount, int* coins, int coinsSize) {
    unsigned long *dp = (unsigned long*)malloc(sizeof(unsigned long) * (amount + 1));

    if (dp == NULL) {
        return -1;
    }

    memset(dp, 0, sizeof(unsigned long) * (amount + 1));
    dp[0] = 1;

    for (int i = 0; i < coinsSize; ++i) {
        for (int j = coins[i]; j <= amount; ++j) {
            dp[j] += dp[j - coins[i]];
        }
    }

    return dp[amount];
}