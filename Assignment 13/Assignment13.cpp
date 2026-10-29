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