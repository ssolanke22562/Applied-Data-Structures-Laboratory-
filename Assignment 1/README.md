# Count Zeroes in a Sorted Binary Array

## Problem Statement
Given an array consisting of only `1`s and `0`s, where all the `1`s appear first followed by all the `0`s, find the total number of `0`s in the array.

**Examples:**
*   **Input:** `[1, 1, 1, 1, 0, 0]` -> **Output:** `2`
*   **Input:** `[1, 0, 0, 0, 0]` -> **Output:** `4`
*   **Input:** `[0, 0, 0]` -> **Output:** `3`
*   **Input:** `[1, 1, 1, 1]` -> **Output:** `0`

## Approach: Binary Search
Since the array is pre-sorted in descending order (all `1`s followed by all `0`s), we can optimize our search instead of counting the elements one by one. 

The goal is to find the **index of the first occurrence of `0`**. Once we know where the `0`s start, we can subtract that index from the total length of the array to get the exact count.

1.  Initialize two pointers: `low = 0` and `high = n - 1`.
2.  Calculate the `mid` index.
3.  If `arr[mid] == 0`:
    *   This might be the first `0`, or there might be more `0`s to the left. 
    *   Record `mid` as a potential answer, but move the `high` pointer to `mid - 1` to keep searching the left half.
4.  If `arr[mid] == 1`:
    *   The `0`s must start somewhere on the right side.
    *   Move the `low` pointer to `mid + 1`.
5.  When the loop terminates, if a `0` was found, the number of zeroes is `total_size - first_zero_index`.

## Complexity Analysis
*   **Time Complexity:** $O(\log n)$. Using binary search cuts the search space in half during each iteration, making it significantly faster than a linear $O(n)$ scan, especially for massive arrays.
*   **Space Complexity:** $O(1)$. No extra space is required as we are only using a few variable pointers.

## How to Run
1.  Ensure you have a C++ compiler installed (like GCC or Clang).
2.  Save the provided code into a file named `main.cpp`.
3.  Compile the code using: `g++ -O2 main.cpp -o count_zeroes`
4.  Run the executable: `./count_zeroes`