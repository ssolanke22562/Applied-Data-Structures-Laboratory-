# Subset Sum Problem (1D Dynamic Programming)

## Problem Statement
Given a set of non-negative integers and a value `sum`, the task is to check if there is a subset of the given set whose sum is equal to the given `sum`.

## Approach
This solution uses a **Bottom-Up 1D Dynamic Programming** approach to solve the problem efficiently. 
* **Space Optimization:** Instead of a traditional 2D DP matrix, it uses a single dynamically allocated boolean array `dp` of size `target_sum + 1`.
* **Backward Traversal:** The inner loop iterates backwards to ensure that each array element is evaluated only once per subset, avoiding the unbounded repetition seen in the Coin Change problem.
* **Core C++:** Built without the Standard Template Library (STL), relying strictly on raw arrays, dynamic memory allocation (`new`/`delete[]`), and `<iostream>`.

## Complexity Analysis
* **Time Complexity:** O(N * sum), where N is the number of elements in the array and `sum` is the target value. The nested loops evaluate each sum possibility for every element.
* **Space Complexity:** O(sum), as the algorithm only requires a 1D boolean array proportional to the target sum.

## Compilation and Execution
1. Save the source code in a file named `subset_sum.cpp`.
2. Open your terminal and compile the code using your MinGW compiler:
   ```bash
   g++ subset_sum.cpp -o subset_sum