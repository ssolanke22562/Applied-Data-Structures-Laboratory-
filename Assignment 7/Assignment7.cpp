#include <iostream>
using namespace std;
bool canComplete(int task[], int n, int d, int limit) 
{
    int days = 1;
    int work = 0;

    for (int i = 0; i < n; i++) 
    {
        if (work + task[i] <= limit) 
        {
            work += task[i];
        } else {
            days++;
            work = task[i];
        }
    }

    return days <= d;
}
int main() 
{
    int n, d;
    cout << "Enter number of tasks: ";
    cin >> n;
    int task[10];
    cout << "Enter task workloads: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> task[i];
    }
    cout << "Enter number of days: ";
    cin >> d;
    int low = task[0];
    int high = 0;
    for (int i = 0; i < n; i++) 
    {
        if (task[i] > low)
        {
            low = task[i];
        }
        high += task[i];
    }
    while (low < high) 
    {
        int mid = low + (high - low) / 2;

        if (canComplete(task, n, d, mid))
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << "Minimum work per day = " << low << endl;
    return 0;
}