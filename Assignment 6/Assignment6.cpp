#include <iostream>

using namespace std;

// Pure O(N) Time, O(1) Auxiliary Space Greedy Solution
long long maxProfitGreedy(const int prices[], int n) {
    if (n <= 1) return 0;

    long long total_profit = 0;
    int max_future_price = 0;

    // Traverse from right to left (Day n-1 down to 0)
    for (int i = n - 1; i >= 0; --i) {
        if (prices[i] > max_future_price) {
            // Found a higher sell target for days prior to day i
            max_future_price = prices[i];
        } else {
            // Greedy choice: buy on day i, sell on the max_future_price day
            total_profit += (max_future_price - prices[i]);
        }
    }

    return total_profit;
}

// Minimal padding helper to replace <iomanip>
void printPaddedInt(long long val, int width) {
    long long temp = val;
    int len = (val == 0) ? 1 : 0;
    if (temp < 0) {
        len++;
        temp = -temp;
    }
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    cout << val;
    for (int i = len; i < width; ++i) cout << ' ';
}

void printPaddedStr(const char* str, int width) {
    int len = 0;
    while (str[len] != '\0') len++;
    cout << str;
    for (int i = len; i < width; ++i) cout << ' ';
}

void displayTradingDetails(const int prices[], int n) {
    if (n <= 0) return;

    // Single backward pass to store selling targets for the display table
    int* max_future = new int[n];
    int current_max = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (prices[i] > current_max) {
            current_max = prices[i];
        }
        max_future[i] = current_max;
    }

    cout << "\n------------------------------------------------------------\n";
    printPaddedStr("Day", 8);
    printPaddedStr("Price", 12);
    printPaddedStr("Action", 22);
    printPaddedStr("Profit Gained", 15);
    cout << "\n------------------------------------------------------------\n";

    long long total_profit = 0;
    for (int i = 0; i < n; ++i) {
        printPaddedInt(i + 1, 8);
        printPaddedInt(prices[i], 12);

        if (prices[i] < max_future[i]) {
            int profit = max_future[i] - prices[i];
            total_profit += profit;

            cout << "Buy (Sell @";
            cout << max_future[i];
            cout << ")";

            int len = 11;
            int temp = max_future[i];
            while (temp > 0) { len++; temp /= 10; }
            for (int s = len; s < 22; ++s) cout << ' ';

            cout << "+" << profit << "\n";
        } else {
            printPaddedStr("Sell / Hold", 22);
            cout << "0\n";
        }
    }

    cout << "------------------------------------------------------------\n";
    cout << "Total Maximum Profit: " << total_profit << "\n\n";

    delete[] max_future;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "============================================================\n";
    cout << "   STOCK TRADING PROFIT MAXIMIZATION (GREEDY ALGORITHM)     \n";
    cout << "============================================================\n";

    int choice;
    cout << "Select Mode:\n";
    cout << "1. Run Default Example Test Cases\n";
    cout << "2. Enter Custom Stock Prices\n";
    cout << "Enter choice (1 or 2): ";

    if (!(cin >> choice)) return 0;

    if (choice == 1) {
        const int tc1[] = {100, 20, 40, 20, 80, 60};
        const int tc2[] = {10, 20, 30, 40, 50};
        const int tc3[] = {50, 40, 30, 20, 10};
        const int tc4[] = {2, 30, 15, 10, 8, 25, 80};

        const int* testCases[] = {tc1, tc2, tc3, tc4};
        const int sizes[] = {6, 5, 5, 7};

        for (int t = 0; t < 4; ++t) {
            cout << "\n>>> Test Case " << (t + 1) << " Stock Prices: [ ";
            for (int i = 0; i < sizes[t]; ++i) cout << testCases[t][i] << " ";
            cout << "]\n";
            displayTradingDetails(testCases[t], sizes[t]);
        }
    } else if (choice == 2) {
        int n;
        cout << "Enter number of days (N): ";
        if (!(cin >> n) || n <= 0) return 0;

        int* prices = new int[n];
        cout << "Enter the stock prices for " << n << " days:\n";
        for (int i = 0; i < n; ++i) {
            cout << "Day " << (i + 1) << ": ";
            cin >> prices[i];
        }

        displayTradingDetails(prices, n);
        delete[] prices;
    }

    return 0;
}