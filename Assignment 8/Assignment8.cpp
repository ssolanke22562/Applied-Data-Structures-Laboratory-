#include <iostream>
#include <vector>
using namespace std;

long long countWays(vector<int>& coins, int sum) {
    vector<long long> dp(sum + 1, 0);

    dp[0] = 1;

    for (int coin : coins) {
        for (int j = coin; j <= sum; j++) {
            dp[j] += dp[j - coin];
        }
    }

    return dp[sum];
}

int main() {
    vector<int> coins = {1, 2, 3};
    int sum = 4;

    cout << countWays(coins, sum);

    return 0;
}
