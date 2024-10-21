int binary_knapsack(int items, int limit, vector<int> &weights,
                    vector<int> &vals) {
    vector<int> dp(limit + 1, 0);

    for (int i = 1; i <= items; ++i)
        for (int curr = limit; curr >= 0; --curr) {
            int prev = i - 1;
            if (weights[prev] <= curr) {
                int val = vals[prev] + dp[curr - weights[prev]];
                dp[curr] = max(dp[curr], val);
            }
        }

    return dp[limit];
}
