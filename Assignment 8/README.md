# Coin Change Problem

## 📌 Problem Statement

Given an array `coins[]` of size `N`, where each element represents a distinct denomination of currency, and an integer `sum`, determine the total number of ways to make the given sum using the available coin denominations.

Each coin can be used an unlimited number of times.

---

## 📝 Example

### Input
```text
coins[] = {1, 2, 3}
sum = 4
```

### Output
```text
4
```

### Explanation

The possible combinations are:

1. {1, 1, 1, 1}
2. {1, 1, 2}
3. {2, 2}
4. {1, 3}

Hence, the total number of ways is **4**.

---

## 🎯 Objective

Find the total number of unique combinations that can be formed to achieve the target sum using the given coin denominations.

---

## ✅ Approach

This problem can be efficiently solved using **Dynamic Programming (DP)**.

### Key Idea

- Create a DP array where `dp[i]` represents the number of ways to make the value `i`.
- Initialize `dp[0] = 1` since there is one way to make sum `0` (by choosing no coins).
- Iterate through each coin and update the DP array accordingly.

---

## 🔹 Algorithm

1. Create a DP array of size `sum + 1` and initialize all values to `0`.
2. Set `dp[0] = 1`.
3. For each coin:
   - Traverse from `coin` to `sum`.
   - Update:
     ```cpp
     dp[j] += dp[j - coin];
     ```
4. Return `dp[sum]`.

---

## 💻 C++ Implementation

```cpp
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
```

---

## 📊 Complexity Analysis

| Complexity | Value |
|------------|--------|
| Time Complexity | O(N × Sum) |
| Space Complexity | O(Sum) |

Where:

- `N` = Number of coin denominations
- `Sum` = Target sum

---

## 🔍 Edge Cases

- `sum = 0` → Output is `1`.
- Empty coin array with non-zero sum → Output is `0`.
- Coin denominations larger than the target sum.
- Duplicate denominations (should be handled appropriately if input constraints allow).

---

## 🚀 Applications

- Financial transaction systems
- Dynamic Programming practice
- Resource allocation problems
- Combinatorial optimization
- Competitive Programming and Coding Interviews

---

## 🏷️ Tags

`Dynamic Programming` `Coin Change` `DP` `Combinatorics` `C++` `Algorithms`

---

## 📚 References

- Dynamic Programming Concepts
- Unbounded Knapsack Pattern
- Coin Change Variants in Competitive Programming