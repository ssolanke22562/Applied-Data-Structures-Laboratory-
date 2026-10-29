# String Transformation Problem (Dynamic Programming)

## 📌 Problem Statement

Given two strings `s1` and `s2` (where `s2` consists exclusively of uppercase English alphabet letters, and `s1` can contain both lowercase and uppercase English letters). 

Determine if it is possible to transform `s1` into `s2` by performing the following operations:
1. **Capitalize:** Change some (zero or more) lowercase letters in `s1` to uppercase.
2. **Delete:** Delete any or all of the remaining lowercase letters in `s1`.

> **Important Rule:** Uppercase letters originally present in `s1` **cannot** be modified or deleted. They must appear in the exact order and match corresponding uppercase letters in `s2`.

---

## 📝 Formal Definition

- **Input:**
  - $s_1$: A string of length $n$ containing characters in range `['a'-'z', 'A'-'Z']`.
  - $s_2$: A string of length $m$ containing characters in range `['A'-'Z']`.
- **Output:**
  - `YES` (or `true`) if $s_1$ can be converted to $s_2$ using the allowed operations.
  - `NO` (or `false`) otherwise.

---

## 💡 Examples

### Example 1: Successful Transformation
- **Input:**
  ```text
  s1 = "daBcd"
  s2 = "ABC"
  ```
- **Output:**
  ```text
  YES
  ```
- **Step-by-step Transformation:**
  1. Delete lowercase `'d'` at index 0 $\rightarrow$ `"aBcd"`
  2. Capitalize lowercase `'a'` at index 1 $\rightarrow$ `"ABcd"`
  3. Keep uppercase `'B'` at index 2 $\rightarrow$ `"ABcd"`
  4. Capitalize lowercase `'c'` at index 3 $\rightarrow$ `"ABCd"`
  5. Delete lowercase `'d'` at index 4 $\rightarrow$ `"ABC"`
  - Transformed string is `"ABC"`, which matches `s2`.

---

### Example 2: Impossible Due to Unmatched Uppercase Letter
- **Input:**
  ```text
  s1 = "argEB"
  s2 = "E"
  ```
- **Output:**
  ```text
  NO
  ```
- **Explanation:**
  - `s1` contains an uppercase `'B'` which cannot be deleted or converted to lowercase.
  - The resulting string must contain both `'E'` and `'B'` (e.g., `"EB"`), which cannot match `"E"`.

---

### Example 3: Target Can Be Formed from All Lowercase
- **Input:**
  ```text
  s1 = "abcdef"
  s2 = "ACE"
  ```
- **Output:**
  ```text
  YES
  ```
- **Explanation:**
  - Capitalize `'a'`, `'c'`, `'e'` to `'A'`, `'C'`, `'E'`.
  - Delete `'b'`, `'d'`, `'f'`.

---

## 🎯 Objective

Solve the string transformation feasibility problem using **Dynamic Programming (DP)** in $\mathcal{O}(N \times M)$ time complexity by evaluating prefix subproblems.

---

## 🧠 Dynamic Programming Approach

This problem resembles the **Longest Common Subsequence (LCS)** / **Edit Distance** family of dynamic programming problems, where decisions are made character-by-character.

### State Definition
Let `dp[i][j]` be a boolean state where:
- `dp[i][j] = true` if the prefix of length `i` of string `s1` (`s1[0 ... i-1]`) can be transformed into the prefix of length `j` of string `s2` (`s2[0 ... j-1]`).
- `dp[i][j] = false` otherwise.

---

### Base Cases

1. **Both prefixes are empty (`i = 0, j = 0`):**
   $$dp[0][0] = true$$
   An empty string trivially matches another empty string.

2. **Empty `s1` and non-empty `s2` (`i = 0, j > 0`):**
   $$dp[0][j] = false$$
   An empty source cannot produce non-empty characters.

3. **Non-empty `s1` and empty `s2` (`i > 0, j = 0`):**
   - If `s1[i - 1]` is lowercase, it can be deleted:
     $$dp[i][0] = dp[i - 1][0]$$
   - If `s1[i - 1]` is uppercase, it cannot be deleted, so transformation is impossible:
     $$dp[i][0] = false$$

---

### State Transitions

For each character $s_1[i - 1]$ and $s_2[j - 1]$:

1. **Matching or Capitalizing:**
   If $s_1[i - 1] == s_2[j - 1]$ OR ($s_1[i - 1]$ is lowercase and $\text{toupper}(s_1[i - 1]) == s_2[j - 1]$):
   $$dp[i][j] = dp[i - 1][j - 1]$$

2. **Deleting Lowercase Character:**
   If $s_1[i - 1]$ is lowercase, we can always choose to delete it:
   $$dp[i][j] = dp[i][j] \lor dp[i - 1][j]$$

3. **Mismatched Uppercase Character:**
   If $s_1[i - 1]$ is uppercase and $s_1[i - 1] \ne s_2[j - 1]$, it can neither match nor be deleted:
   $$dp[i][j] = false$$

---

## 🔹 Algorithm

1. Initialize a 2D boolean array `dp` of size $(N + 1) \times (M + 1)$ with `false`.
2. Set `dp[0][0] = true`.
3. Fill the first column `dp[i][0]` for all $1 \le i \le N$:
   - If `s1[i - 1]` is lowercase, `dp[i][0] = dp[i - 1][0]`.
4. Iterate $i$ from $1$ to $N$ and $j$ from $1$ to $M$:
   - Check if $s_1[i - 1]$ matches $s_2[j - 1]$ directly or by capitalizing:
     `dp[i][j] = dp[i - 1][j - 1]`
   - If $s_1[i - 1]$ is lowercase, check if deleting it gives a valid state:
     `dp[i][j] = dp[i][j] || dp[i - 1][j]`
5. Return `dp[N][M]`.

---

## 💻 C++ Implementation

```cpp
#include <iostream>
#include <string>
using namespace std;

bool canTransform(string s1, string s2) {
    int n = s1.length();
    int m = s2.length();

    bool dp[1001][1001] = {false};

    dp[0][0] = true;

    // Initialize first column (handling empty s2)
    for (int i = 1; i <= n; i++) {
        if (s1[i - 1] >= 'a' && s1[i - 1] <= 'z')
            dp[i][0] = dp[i - 1][0];
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            // Check whether characters match or lowercase can be converted to uppercase
            if (s1[i - 1] == s2[j - 1] ||
                (s1[i - 1] >= 'a' && s1[i - 1] <= 'z' &&
                 s1[i - 1] - 32 == s2[j - 1])) {

                dp[i][j] = dp[i - 1][j - 1];
            }

            // Delete lowercase characters
            if (s1[i - 1] >= 'a' && s1[i - 1] <= 'z') {
                dp[i][j] = dp[i][j] || dp[i - 1][j];
            }
        }
    }

    return dp[n][m];
}

int main() {
    string s1 = "daBcd";
    string s2 = "ABC";

    if (canTransform(s1, s2))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
```

---

## 📊 Complexity Analysis

| Complexity | Value | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N \times M)$ | Nested loops iterate through all states of length $N$ and $M$. |
| **Space Complexity** | $\mathcal{O}(N \times M)$ | Auxiliary 2D DP matrix of size $(N + 1) \times (M + 1)$. |

*Where:*
- $N$ = Length of string $s_1$
- $M$ = Length of string $s_2$

---

## 🔍 Edge Cases

1. **Both Strings Empty:**
   - Result: `YES` ($dp[0][0] = true$).
2. **$s_1$ is Shorter than $s_2$ ($N < M$):**
   - Cannot expand characters, so result will naturally evaluate to `NO`.
3. **Extra Uppercase Characters in $s_1$:**
   - Cannot be deleted, accurately leads to `NO`.
4. **All Lowercase $s_1$:**
   - Flexible deletion and capitalization allowed.
5. **No Characters Needed from $s_1$ ($s_2$ is empty):**
   - Result is `YES` only if all characters in $s_1$ are lowercase (all deleted).

---

## 🚀 Applications

- **Compiler Case-Insensitive Token Matching:** Parsing flexible identifiers in language compilers.
- **Query Normalization & Search Engines:** Matching abbreviations with expanded acronyms.
- **Bioinformatics:** Sequence alignment with deletion of low-confidence markers.
- **Text Processing & Auto-Correction:** Spell checkers aligning user abbreviations with capitalized keywords.

---

## 🏷️ Tags

`Dynamic Programming` `Strings` `LCS Variant` `Edit Distance` `Algorithms` `C++`
