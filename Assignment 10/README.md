# Subset Sum Problem

## 📌 Problem Statement

Given a set of non-negative integers `arr[]` and a target value `sum`, the task is to determine whether there exists a subset of the given set whose elements sum up to exactly equal the given `sum`.

Each element from the set can either be **included** or **excluded** (used at most once, adhering to the 0/1 Knapsack principle).

---

## 📝 Formal Definition

- **Input:** 
  - An array or set of non-negative integers: $arr = \{a_1, a_2, \dots, a_n\}$ where $a_i \ge 0$.
  - An integer: $sum \ge 0$.
- **Output:** 
  - `True` if there exists an index subset $S \subseteq \{1, 2, \dots, n\}$ such that:
    $$\sum_{i \in S} a_i = sum$$
  - `False` otherwise.

---

## 💡 Examples

### Example 1: Standard Positive Case
- **Input:**
  ```text
  arr[] = {3, 34, 4, 12, 5, 2}
  sum   = 9
  ```
- **Output:**
  ```text
  True
  Subset: {5, 4} (or {3, 4, 2})
  ```
- **Explanation:**
  - $5 + 4 = 9$ (or $3 + 4 + 2 = 9$). Since a valid subset exists, the result is `True`.

---

### Example 2: Impossible Target Case
- **Input:**
  ```text
  arr[] = {3, 34, 4, 12, 5, 2}
  sum   = 30
  ```
- **Output:**
  ```text
  False
  ```
- **Explanation:**
  - No combination of elements in the array can sum up to 30.

---

### Example 3: Base Case (Sum = 0)
- **Input:**
  ```text
  arr[] = {1, 2, 7}
  sum   = 0
  ```
- **Output:**
  ```text
  True
  Subset: {} (Empty subset)
  ```
- **Explanation:**
  - An empty subset $\emptyset$ always has a sum of 0.

---

## 🎯 Objective

Determine the existence of a subset summing to the target value in polynomial time using **Dynamic Programming**, and reconstruct the subset elements by backtracking the state transitions.

---

## 🧠 Dynamic Programming Approaches

The problem exhibits **optimal substructure** and **overlapping subproblems**, making it an ideal candidate for Dynamic Programming.

### 1. 2D Dynamic Programming (Tabulation)

#### State Definition
Let `dp[i][j]` be a boolean state representing whether a subset of the first `i` elements (`arr[0 ... i-1]`) can sum up to `j`.

#### Base Cases
1. `dp[i][0] = true` for all $0 \le i \le n$:
   - A sum of `0` is always possible by choosing an empty subset $\emptyset$.
2. `dp[0][j] = false` for all $1 \le j \le sum$:
   - With `0` elements, it is impossible to form any positive sum $j > 0$.

#### State Transitions
For each element $arr[i - 1]$ and target sum $j$:
- **Exclude the element:** If $arr[i - 1] > j$, the element cannot be included:
  $$dp[i][j] = dp[i - 1][j]$$
- **Include or Exclude:** If $arr[i - 1] \le j$, we check if the sum can be formed either without this element or with this element:
  $$dp[i][j] = dp[i - 1][j] \lor dp[i - 1][j - arr[i - 1]]$$

#### Final Answer
The answer is stored in:
$$dp[n][sum]$$

---

### 2. Subset Reconstruction (Backtracking)

To find the actual elements that form the sum:
1. Start from cell $(i = n, \text{currSum} = sum)$.
2. If $dp[i][\text{currSum}] == dp[i - 1][\text{currSum}]$, the $i$-th element was **not** needed to form $\text{currSum}$. Move to $i - 1$.
3. If $dp[i - 1][\text{currSum}]$ is `false` and $dp[i - 1][\text{currSum} - arr[i - 1]]$ is `true`, include $arr[i - 1]$ in the subset, set $\text{currSum} = \text{currSum} - arr[i - 1]$, and move to $i - 1$.
4. Repeat until $\text{currSum} = 0$.

---

### 3. Space-Optimized 1D Dynamic Programming

Since each row $dp[i]$ only depends on the previous row $dp[i - 1]$:
- We can maintain a single 1D boolean array `dp[0 ... sum]`.
- Iterate through each number in the array.
- Traverse the target sum **backwards** from $sum$ down to $arr[i]$:
  $$dp[j] = dp[j] \lor dp[j - arr[i]]$$
- **Why backwards?** Backwards traversal ensures that each element is used at most once (0/1 Knapsack property) and prevents unbounded reuse.

---

## 💻 C++ Implementation

```cpp
#include <iostream>
#include <vector>

using namespace std;

// 2D Dynamic Programming with Subset Reconstruction
bool isSubsetSum(const vector<int>& arr, int targetSum, vector<int>& subset) {
    int n = arr.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));

    // Base cases
    for (int i = 0; i <= n; i++) dp[i][0] = true;
    for (int j = 1; j <= targetSum; j++) dp[0][j] = false;

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= targetSum; j++) {
            if (arr[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    // Reconstruct subset
    if (dp[n][targetSum]) {
        int curr = targetSum;
        for (int i = n; i > 0 && curr > 0; i--) {
            if (!dp[i - 1][curr] && dp[i - 1][curr - arr[i - 1]]) {
                subset.push_back(arr[i - 1]);
                curr -= arr[i - 1];
            }
        }
    }

    return dp[n][targetSum];
}
```

---

## 📊 Complexity Analysis

| Approach | Time Complexity | Auxiliary Space Complexity | Reconstructs Subset? |
| :--- | :--- | :--- | :--- |
| **2D Dynamic Programming** | $\mathcal{O}(N \times \text{sum})$ | $\mathcal{O}(N \times \text{sum})$ | Yes (via back-tracking) |
| **1D Space Optimized DP** | $\mathcal{O}(N \times \text{sum})$ | $\mathcal{O}(\text{sum})$ | No (membership only) |
| **Brute Force (Recursion)** | $\mathcal{O}(2^N)$ | $\mathcal{O}(N)$ recursion stack | Yes |

*Where:*
- $N$ = Number of elements in the set.
- $\text{sum}$ = Target sum.

---

## 🔍 Edge Cases

1. **Target Sum is Zero (`sum = 0`):**
   - Result is always `True` since the empty set has a sum of 0.
2. **Empty Array (`n = 0`) with `sum > 0`:**
   - Result is always `False`.
3. **Element Greater than Target (`arr[i] > sum`):**
   - The element cannot be part of the subset and is skipped automatically.
4. **All Elements Greater than Target:**
   - Result is `False` (for `sum > 0`).
5. **Exact Match:**
   - When an element itself equals `sum`, it directly forms a valid single-element subset.

---

## 🚀 Applications

- **0/1 Knapsack Problem Variant:** Direct foundation for the 0/1 Knapsack and Partition Equal Subset Sum problems.
- **Financial and Billing Systems:** Reconciling ledger payments and invoice splitting.
- **Resource Allocation:** Distributing computational or load capacity across fixed hardware nodes.
- **Cryptography:** Merkle-Hellman knapsack cryptosystems.

---

## 🏷️ Tags

`Dynamic Programming` `Subset Sum` `0/1 Knapsack` `Algorithms` `C++` `Tabulation`
