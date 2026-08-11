#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countZeroes(const vector<int>& arr) {
        int n = arr.size();
        int low = 0;
        int high = n - 1;
        int firstZeroIndex = -1;

        // Binary search to find the first occurrence of 0
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == 0) {
                firstZeroIndex = mid; // Record the index
                high = mid - 1;       // Check left side for an earlier 0
            } 
            else { // arr[mid] == 1
                low = mid + 1;        // 0s must be on the right side
            }
        }

        // If no 0 was found in the entire array
        if (firstZeroIndex == -1) {
            return 0;
        }

        // The number of 0s is the total length minus the index of the first 0
        return n - firstZeroIndex;
    }
};

int main() {
    Solution sol;
    
    // Test Cases
    vector<int> test1 = {1, 1, 1, 1, 0, 0};
    vector<int> test2 = {1, 0, 0, 0, 0, 0};
    vector<int> test3 = {0, 0, 0, 0};
    vector<int> test4 = {1, 1, 1, 1, 1};
    
    cout << "Test 1 [1, 1, 1, 1, 0, 0] -> Zeroes count: " << sol.countZeroes(test1) << endl;
    cout << "Test 2 [1, 0, 0, 0, 0, 0] -> Zeroes count: " << sol.countZeroes(test2) << endl;
    cout << "Test 3 [0, 0, 0, 0]       -> Zeroes count: " << sol.countZeroes(test3) << endl;
    cout << "Test 4 [1, 1, 1, 1, 1]    -> Zeroes count: " << sol.countZeroes(test4) << endl;

    return 0;
}