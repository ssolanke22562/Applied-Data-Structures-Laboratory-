#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& arr) {
        int nonZeroIndex = 0; // Pointer for the next non-zero element

        for (int i = 0; i < arr.size(); i++) {
            // If the current element is not 0, swap it to the nonZeroIndex
            if (arr[i] != 0) {
                swap(arr[nonZeroIndex], arr[i]);
                nonZeroIndex++; // Move the pointer forward
            }
        }
    }
};

// Helper function to print arrays easily
void printArray(const vector<int>& arr) {
    cout << "[";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << (i < arr.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Cases
    vector<int> test1 = {1, 2, 0, 4, 3, 0, 5, 0};
    vector<int> test2 = {0, 0, 1};
    vector<int> test3 = {4, 5, 6};
    vector<int> test4 = {0, 0, 0, 0};
    
    // Execution and Output
    cout << "Original: "; printArray(test1);
    sol.moveZeroes(test1);
    cout << "Modified: "; printArray(test1);
    cout << "-----------------------" << endl;

    cout << "Original: "; printArray(test2);
    sol.moveZeroes(test2);
    cout << "Modified: "; printArray(test2);
    cout << "-----------------------" << endl;

    cout << "Original: "; printArray(test3);
    sol.moveZeroes(test3);
    cout << "Modified: "; printArray(test3);
    cout << "-----------------------" << endl;

    cout << "Original: "; printArray(test4);
    sol.moveZeroes(test4);
    cout << "Modified: "; printArray(test4);

    return 0;
}