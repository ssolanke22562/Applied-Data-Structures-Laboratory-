#include <iostream>
using namespace std;

bool isSubsetSum(int arr[], int n, int target_sum) {
    bool* dp = new bool[target_sum + 1];

    for (int i = 0; i <= target_sum; i++) {
        dp[i] = false;
    }

    dp[0] = true;

    for (int i = 0; i < n; i++) {
        int current_val = arr[i];

        for (int j = target_sum; j >= current_val; j--) {
            if (dp[j - current_val] == true) {
                dp[j] = true;
            }
        }
    }

    bool result = dp[target_sum];

    delete[] dp;

    return result;
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    int target_sum = 9;

    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSubsetSum(arr, n, target_sum)) {
        cout << "True: A subset with the given sum exists." << endl;
    } else {
        cout << "False: No subset with the given sum exists." << endl;
    }

    return 0;
}
