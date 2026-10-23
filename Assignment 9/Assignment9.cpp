#include <iostream>

using namespace std;

bool isSubsetSum(int arr[], int n, int target_sum) {
    // Dynamically allocate the array since target_sum can vary
    bool* dp = new bool[target_sum + 1];
    
    // Initialize all sums to false
    for (int i = 0; i <= target_sum; i++) {
        dp[i] = false;
    }
    
    // Base case: A sum of 0 is always possible
    dp[0] = true;
    
    // Process each number in the array one by one
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        
        // Traverse backwards to ensure each number is only used once
        for (int j = target_sum; j >= num; j--) {
            if (dp[j - num] == true) {
                dp[j] = true;
            }
        }
    }
    
    // Save the answer before deleting the array to prevent memory leaks
    bool result = dp[target_sum];
    delete[] dp;
    
    return result;
}

int main() {
    int arr[] = {3, 34, 4, 12, 5, 2};
    int target_sum = 9;
    
    // Calculate the number of elements in the raw array
    int n = sizeof(arr) / sizeof(arr[0]);
    
    if (isSubsetSum(arr, n, target_sum)) {
        cout << "True: Subset exists." << endl;
    } else {
        cout << "False: Subset does not exist." << endl;
    }
    
    return 0;
}