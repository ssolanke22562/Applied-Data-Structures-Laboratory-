#include <iostream>
#include <string>
using namespace std;

bool canTransform(string s1, string s2) {
    int n = s1.length();
    int m = s2.length();

    bool dp[1001][1001] = {false};

    dp[0][0] = true;

    // Initialize first column
    for (int i = 1; i <= n; i++) {
        if (s1[i - 1] >= 'a' && s1[i - 1] <= 'z')
            dp[i][0] = dp[i - 1][0];
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            // Check whether characters match
            // or lowercase can be converted to uppercase
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
