#include <bits/stdc++.h>
using namespace std;

int minWeightLoss(int target, vector<int> weights) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];
            if (weights[i - 1] <= j) {
                int loss = j - weights[i - 1];
                dp[i][j] = max(dp[i][j], dp[i - 1][j - weights[i - 1]] + loss);
            }
        }
    }
    return target - dp[n][target];
}

int main() {
    int target = 5;
    vector<int> weights = {1, 2, 3};
    cout << minWeightLoss(target, weights) << endl;
    return 0;
}