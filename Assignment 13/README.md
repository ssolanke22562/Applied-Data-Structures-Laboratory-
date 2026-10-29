# Distinct Subsets using Bit Masking Approach

## 📌 Problem Statement

Given an array of integers `arr[]` of size `N`, the task is to generate and display all its **distinct subsets** (the power set). 

A subset cannot contain duplicate identical representations; any repeated subset resulting from duplicate elements in the original array must be considered and printed **only once** in the output.

---

## 📝 Formal Definition

- **Input:** 
  - An integer $N$ representing the number of elements.
  - An array of integers: $arr = [a_0, a_1, \dots, a_{N-1}]$.
- **Output:** 
  - All unique subsets $S \subseteq arr$ such that no two subsets in the output are identical.
- **Constraints:**
  - $0 \le N \le 10$ (for $2^{10} = 1024$ subsets).
  - Array elements can be positive, negative, or zero, and may contain duplicates.

---

## 💡 Examples

### Example 1: Distinct Elements
- **Input:**
  ```text
  N = 3
  arr = {1, 2, 3}
  ```
- **Output:**
  ```text
  { }
  { 1 }
  { 2 }
  { 1 2 }
  { 3 }
  { 1 3 }
  { 2 3 }
  { 1 2 3 }
  ```
- **Explanation:**
  - Total subsets = $2^3 = 8$. Since all elements are unique, all 8 subsets are distinct.

---

### Example 2: Array Containing Duplicate Elements
- **Input:**
  ```text
  N = 3
  arr = {1, 2, 2}
  ```
- **Output:**
  ```text
  { }
  { 1 }
  { 2 }
  { 1 2 }
  { 2 2 }
  { 1 2 2 }
  ```
- **Explanation:**
  - Total generated raw subsets = $2^3 = 8$:
    - `mask = 0 (000)` $\rightarrow$ `{ }`
    - `mask = 1 (001)` $\rightarrow$ `{ 1 }`
    - `mask = 2 (010)` $\rightarrow$ `{ 2 }` (using first 2)
    - `mask = 3 (011)` $\rightarrow$ `{ 1, 2 }`
    - `mask = 4 (100)` $\rightarrow$ `{ 2 }` *(Duplicate of mask 2 - skipped)*
    - `mask = 5 (101)` $\rightarrow$ `{ 1, 2 }` *(Duplicate of mask 3 - skipped)*
    - `mask = 6 (110)` $\rightarrow$ `{ 2, 2 }`
    - `mask = 7 (111)` $\rightarrow$ `{ 1, 2, 2 }`
  - Distinct subsets retained = **6**.

---

## 🎯 Objective

Leverage the binary representation of integers (Bit Manipulation / Bit Masking) to systematically enumerate all $2^N$ possible subset combinations, while maintaining a lookup mechanism to filter out duplicates.

---

## ⚙️ Core Concept: Bit Masking Approach

### Why Bit Masking?
For an array of $N$ elements, each element has exactly **two choices**:
1. **Include** the element in the subset (represented by bit `1`).
2. **Exclude** the element from the subset (represented by bit `0`).

Thus, there are $2^N$ total subsets, precisely matching binary numbers from $0$ to $2^N - 1$.

### Bitwise Operation Mapping
- **Total Subsets Limit:** $2^N$ is computed using repeated multiplication or bit shift `(1 << n)`.
- **Inclusion Test:** To check if the $i$-th element is included in subset `mask`:
  $$\text{Included} \iff (\text{mask} \ \& \ (1 \ll i)) \ne 0$$

### Bitmask Representation Table ($N = 3$, $arr = \{A, B, C\}$)

| Mask (Decimal) | Binary Mask | Bit 2 ($C$) | Bit 1 ($B$) | Bit 0 ($A$) | Resulting Subset |
| :---: | :---: | :---: | :---: | :---: | :--- |
| `0` | `000` | 0 | 0 | 0 | `{ }` |
| `1` | `001` | 0 | 0 | 1 | `{ A }` |
| `2` | `010` | 0 | 1 | 0 | `{ B }` |
| `3` | `011` | 0 | 1 | 1 | `{ A, B }` |
| `4` | `100` | 1 | 0 | 0 | `{ C }` |
| `5` | `101` | 1 | 0 | 1 | `{ A, C }` |
| `6` | `110` | 1 | 1 | 0 | `{ B, C }` |
| `7` | `111` | 1 | 1 | 1 | `{ A, B, C }` |

---

## 🛡️ Duplicate Handling Logic

To guarantee that duplicate subsets are not displayed:
1. Store all previously accepted subsets in a 2D array `subsets[1024][10]` and their respective sizes in `sizes[1024]`.
2. Before printing a newly generated subset `current[]` of size `size`:
   - Check against each stored subset $i$ from $0$ to $\text{total} - 1$.
   - If `sizes[i] == size`, compare element-by-element.
   - If all elements match, mark as duplicate (`isDuplicate = true`) and skip.
3. If not duplicate:
   - Print the subset.
   - Append to `subsets[total]` and increment `total`.

---

## 🔹 Algorithm

1. Read $N$ and the array elements $arr[0 \dots N-1]$.
2. Calculate $\text{limit} = 2^N$.
3. Initialize `total = 0` (count of distinct subsets stored).
4. Loop through every integer `mask` from $0$ to $\text{limit} - 1$:
   - Initialize temporary array `current[]` and `size = 0`.
   - Loop `i` from $0$ to $N - 1$:
     - If `(mask & (1 << i)) != 0`, append $arr[i]$ to `current[]` and increment `size`.
   - Call `isDuplicate(current, size)`:
     - If `false`:
       - Print the subset `{ current[0] ... current[size-1] }`.
       - Store `current[]` into `subsets[total]`.
       - Store `size` into `sizes[total]`.
       - Increment `total`.
5. Terminate when all masks are evaluated.

---

## 💻 C++ Implementation

```cpp
#include <iostream>
using namespace std;

int subsets[1024][10];
int sizes[1024];
int total = 0;

bool isDuplicate(int current[], int size) {
    for (int i = 0; i < total; i++) {
        if (sizes[i] != size)
            continue;

        bool same = true;

        for (int j = 0; j < size; j++) {
            if (subsets[i][j] != current[j]) {
                same = false;
                break;
            }
        }

        if (same)
            return true;
    }

    return false;
}

void findDistinctSubsets(int arr[], int n) {
    int limit = 1;

    for (int i = 0; i < n; i++)
        limit = limit * 2;

    for (int mask = 0; mask < limit; mask++) {
        int current[10];
        int size = 0;

        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) != 0) {
                current[size] = arr[i];
                size++;
            }
        }

        if (!isDuplicate(current, size)) {
            cout << "{ ";

            for (int i = 0; i < size; i++) {
                cout << current[i] << " ";
            }

            cout << "}" << endl;

            for (int i = 0; i < size; i++) {
                subsets[total][i] = current[i];
            }

            sizes[total] = size;
            total++;
        }
    }
}

int main() {
    int n;
    int arr[10];

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    findDistinctSubsets(arr, n);

    return 0;
}
```

---

## 📊 Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(2^N \times N + 2^N \times K)$ | $2^N$ masks are evaluated, each taking $\mathcal{O}(N)$ to construct, plus duplicate comparison over $K$ distinct subsets. |
| **Space Complexity** | $\mathcal{O}(2^N \times N)$ | Storing up to $2^N$ subsets of size up to $N$ in the `subsets[1024][10]` table. |

*Where:*
- $N$ = Number of elements in the array ($N \le 10$).
- $K$ = Number of unique subsets ($K \le 2^N$).

---

## 🔍 Edge Cases

1. **Empty Set ($N = 0$):**
   - Output contains only the empty subset `{ }`.
2. **All Identical Elements (e.g., `{5, 5, 5}`):**
   - Subsets generated: `{ }`, `{ 5 }`, `{ 5 5 }`, `{ 5 5 5 }` (only $N + 1$ distinct subsets).
3. **Negative and Zero Values:**
   - Handled correctly without any arithmetic overflow.
4. **Already Unique Elements:**
   - Outputs all $2^N$ subsets without discarding any.

---

## 🚀 Applications

- **Combinatorial Generation & Power Sets:** Enumerating search spaces for subset problems (0/1 Knapsack, Subset Sum).
- **Boolean Satisfiability & Circuit Testing:** Generating all $2^N$ input combinations for logic verification.
- **Machine Learning Feature Selection:** Testing all possible subsets of features to evaluate model accuracy.
- **Cryptography:** Key generation and brute-force key search simulations.

---

## 🏷️ Tags

`Bit Manipulation` `Bitmasking` `Subsets` `Power Set` `Combinatorics` `Algorithms` `C++`
