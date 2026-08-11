# Activity Selection with K Persons

## Problem Statement
Given two arrays `S[]` and `E[]` of size `N` denoting the starting and closing times of shops, and an integer `K` denoting the number of people, find the maximum number of shops they can visit optimally.
*   A shop can be visited by only one person.
*   A person cannot visit another shop if its timing collides with their current one.

## Approach: Greedy Strategy with Multiset
To maximize the total number of shops visited, we need to assign shops in a way that minimizes the "wasted" or idle time between visits. 

1. **Sort by Ending Time:** First, pair the start and end times and sort the shops based on their **ending times** in ascending order. This standard greedy step ensures we always consider the shop that finishes earliest, leaving maximum time for future shops.
2. **Track Free Time:** Use a balanced binary search tree (like `std::multiset` in C++) to keep track of the times when each of the $K$ persons becomes free.
3. **Optimal Assignment:** For each shop, we don't just assign it to *any* free person. We assign it to the person whose free time is **closest to, but less than or equal to**, the shop's start time. 
   * *Why?* If we have an activity starting at 6, and two people are free at time 2 and time 5, assigning the person free at 5 leaves the person free at 2 available for another activity that might have started at 3.
4. **Update:** Once assigned, remove that person's old free time from the multiset, insert the new shop's end time, and increment your visited count.

## Complexity Analysis
*   **Time Complexity:** $O(N \log N + N \log K)$. Sorting the arrays takes $O(N \log N)$. For each of the $N$ shops, querying and updating the `multiset` takes $O(\log K)$ time.
*   **Space Complexity:** $O(N + K)$. We use $O(N)$ space to store the pairs of shop timings and $O(K)$ space for the multiset tracking the people.