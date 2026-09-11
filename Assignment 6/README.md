# Assignment 6: Maximize Profit by Trading Stocks (Greedy Approach)

## 📌 Problem Statement

Given an array `arr[]` of $N$ positive integers denoting the cost of selling and buying stock on each of the $N$ consecutive days. 

On each day, you have three possible actions:
1. **Buy** 1 share of stock at price `arr[i]`.
2. **Sell** all previously bought shares of stock at price `arr[i]`.
3. **Do Nothing** (Hold).

The task is to find the **maximum profit** that can be earned by trading stocks according to these rules.

---

## 💡 Greedy Strategy & Intuition

### Key Insight: Backward Traversal (Right-to-Left)
- In a forward pass (left-to-right), deciding whether to buy on day $i$ requires knowledge of the future maximum price after day $i$.
- If we instead traverse **backwards** from the last day ($n-1$) to the first day ($0$):
  - We maintain `max_future_price` — the highest selling price encountered so far to the right.
  - For any day $i$:
    - If `prices[i] > max_future_price`: Update `max_future_price = prices[i]`. This day is a new peak selling target for stocks bought prior to day $i$.
    - If `prices[i] <= max_future_price`: It is greedy-optimal to buy 1 share on day $i$ and sell it at `max_future_price`. The profit added is `max_future_price - prices[i]`.

---

## 📝 Step-by-Step Algorithm & Pseudocode

### Algorithm
1. If $n \le 1$, return `0` (no transactions possible).
2. Initialize `total_profit = 0` and `max_future_price = 0`.
3. Loop backwards from index $i = n - 1$ down to $0$:
   - If `prices[i] > max_future_price`:
     - Update `max_future_price = prices[i]`
   - Else:
     - Add `(max_future_price - prices[i])` to `total_profit`.
4. Return `total_profit`.

### C++ Function Implementation
```cpp
long long maxProfitGreedy(const int prices[], int n) {
    if (n <= 1) return 0;

    long long total_profit = 0;
    int max_future_price = 0;

    // Traverse from right to left (Day n-1 down to 0)
    for (int i = n - 1; i >= 0; --i) {
        if (prices[i] > max_future_price) {
            max_future_price = prices[i];
        } else {
            total_profit += (max_future_price - prices[i]);
        }
    }

    return total_profit;
}
```

---

## 🔍 Dry Run Example

### Input: `prices = [100, 20, 40, 20, 80, 60]`, $n = 6$

| Day ($i$) | Price (`prices[i]`) | Max Future Price (`max_future_price`) | Action / Decision | Profit Gained | Running Total Profit |
| :---: | :---: | :---: | :---: | :---: | :---: |
| 6 (index 5) | 60 | 60 | Peak Sell / Hold | 0 | 0 |
| 5 (index 4) | 80 | 80 | Update Peak Sell Target | 0 | 0 |
| 4 (index 3) | 20 | 80 | Buy (Sell @ 80) | $+60$ ($80 - 20$) | 60 |
| 3 (index 2) | 40 | 80 | Buy (Sell @ 80) | $+40$ ($80 - 40$) | 100 |
| 2 (index 1) | 20 | 80 | Buy (Sell @ 80) | $+60$ ($80 - 20$) | 160 |
| 1 (index 0) | 100 | 100 | Update Peak Sell Target | 0 | **160** |

**Total Maximum Profit = 160**

---

## 📊 Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N)$ | Single backward linear scan through the array of size $N$. |
| **Auxiliary Space** | $\mathcal{O}(1)$ | The core greedy function uses only constant extra memory (`total_profit`, `max_future_price`, and loop counter). |

---

## 💻 Program Architecture ([Assignment6.cpp](file:///c:/Users/sarth/OneDrive/Desktop/Sem%205/ADSL/Assignment%206/Assignment6.cpp))

- **Dependency-Free Design**: Implemented purely using standard `<iostream>` without relying on STL containers (`<vector>`) or `<iomanip>`.
- **Custom Fast Table Formatter**: Custom lightweight routines `printPaddedInt()` and `printPaddedStr()` provide aligned tabular output.
- **Dynamic Memory Management**: Uses dynamic allocation (`new[]` / `delete[]`) for dynamic custom input arrays.
- **Fast I/O**: Configured with `ios_base::sync_with_stdio(false); cin.tie(NULL);`.
- **Menu-Driven Interface**:
  - `Mode 1`: Runs a suite of 4 diverse test cases (including increasing, decreasing, and fluctuating price trends).
  - `Mode 2`: Accepts user input for $N$ and custom day-by-day stock prices.

---

## 🚀 How to Compile and Run

### 1. Compilation
```powershell
g++ -std=c++17 -Wall -Wextra -O2 Assignment6.cpp -o Assignment6.exe
```

### 2. Execution
```powershell
.\Assignment6.exe
```

### 3. Sample Execution Output

```text
============================================================
   STOCK TRADING PROFIT MAXIMIZATION (GREEDY ALGORITHM)     
============================================================
Select Mode:
1. Run Default Example Test Cases
2. Enter Custom Stock Prices
Enter choice (1 or 2): 1

>>> Test Case 1 Stock Prices: [ 100 20 40 20 80 60 ]

------------------------------------------------------------
Day     Price       Action                Profit Gained  
------------------------------------------------------------
1       100         Sell / Hold           0
2       20          Buy (Sell @80)        +60
3       40          Buy (Sell @80)        +40
4       20          Buy (Sell @80)        +60
5       80          Sell / Hold           0
6       60          Sell / Hold           0
------------------------------------------------------------
Total Maximum Profit: 160
```
