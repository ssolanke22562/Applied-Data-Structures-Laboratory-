# Move All Zeroes to the End

## Problem Statement
Given an array of random integers, push all the `0`s to the end of the array while maintaining the relative order of the non-zero elements. The operation must be done in-place without making a copy of the array.

**Examples:**
*   **Input:** `[1, 2, 0, 4, 3, 0, 5, 0]` -> **Output:** `[1, 2, 4, 3, 5, 0, 0, 0]`
*   **Input:** `[0, 0, 1]` -> **Output:** `[1, 0, 0]`
*   **Input:** `[4, 5, 6]` -> **Output:** `[4, 5, 6]`

## Approach: Two Pointers (Index Tracking)
We can solve this optimally using an index tracker for the non-zero elements.

1.  Initialize a variable `nonZeroIndex` to `0`. This pointer keeps track of where the next non-zero element should be placed.
2.  Iterate through the array using a standard loop with index `i`.
3.  Whenever we encounter a non-zero element (`arr[i] != 0`), we swap it with the element at `arr[nonZeroIndex]`.
4.  After the swap, increment `nonZeroIndex` by 1.
5.  All zeroes are naturally pushed towards the back as they get swapped out by upcoming non-zero elements.

## Complexity Analysis
*   **Time Complexity:** $O(n)$. We only iterate through the array exactly once, making it highly efficient.
*   **Space Complexity:** $O(1)$. The operations are performed entirely in-place, requiring no extra memory for arrays.

## How to Run
1.  Ensure you have a C++ compiler installed (like GCC or Clang).
2.  Save the provided code into a file named `main.cpp`.
3.  Compile the code using: `g++ -O2 main.cpp -o move_zeroes`
4.  Run the executable: `./move_zeroes`