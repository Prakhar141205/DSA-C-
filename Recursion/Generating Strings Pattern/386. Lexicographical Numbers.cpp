/*
LeetCode 386. Lexicographical Numbers
C++ solutions: brute-force sorting, string sorting, DFS, and iterative optimal.

Copy ONE class at a time and rename it to Solution for LeetCode.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: Brute force by sorting numbers as strings.
- Put numbers 1..n into a vector.
- Compare their string representations lexicographically.
Time: O(n log n * L), where L = number of digits (at most 5 here).
Space: O(n * L) for storing strings during sorting.
*/
class Solution1 {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);

        sort(nums.begin(), nums.end(), [](int a, int b) {
            return to_string(a) < to_string(b);
        });

        return nums;
    }
};

/*
Approach 2: Sort strings directly.
This makes the lexicographical comparison explicit, but stores strings.
Time: O(n log n * L)
Space: O(n * L)
*/
class Solution2 {
public:
    vector<int> lexicalOrder(int n) {
        vector<string> words;
        words.reserve(n);

        for (int i = 1; i <= n; ++i)
            words.push_back(to_string(i));

        sort(words.begin(), words.end());

        vector<int> answer;
        answer.reserve(n);
        for (const string& word : words)
            answer.push_back(stoi(word));

        return answer;
    }
};

/*
Approach 3: DFS / preorder traversal (same idea as the user's solution).
Think of numbers as a ten-way prefix tree:
1 -> 10, 11, ..., 19; then backtrack to 2, 3, ...
Visit a number before its children to get lexicographical order.

Time: O(n), because every valid number is visited once.
Auxiliary space: O(log_10(n)) recursion depth, excluding output.
*/
class Solution3 {
    void dfs(int current, int n, vector<int>& answer) {
        if (current > n) return;

        answer.push_back(current);

        for (int digit = 0; digit <= 9; ++digit) {
            long long next = 1LL * current * 10 + digit;
            if (next > n) break;
            dfs(static_cast<int>(next), n, answer);
        }
    }

public:
    vector<int> lexicalOrder(int n) {
        vector<int> answer;
        answer.reserve(n);

        for (int first = 1; first <= 9; ++first) {
            if (first > n) break;
            dfs(first, n, answer);
        }

        return answer;
    }
};

/*
Approach 4: Iterative traversal (optimal O(n) time and O(1) extra space,
excluding the required output vector).

Rules:
1. If current * 10 <= n, descend to the first child.
2. Otherwise, move right to the next sibling.
3. If the next sibling exceeds n, remove trailing 9s (move back up),
   then increment to the next available sibling.
*/
class Solution4 {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> answer;
        answer.reserve(n);

        int current = 1;

        for (int i = 0; i < n; ++i) {
            answer.push_back(current);

            if (1LL * current * 10 <= n) {
                current *= 10;
            } else {
                while (current % 10 == 9 || current + 1 > n) {
                    current /= 10;
                }
                ++current;
            }
        }

        return answer;
    }
};

/*
Dry run for n = 13 (DFS / preorder):
Start at 1:
1 -> 10 -> 11 -> 12 -> 13
No more children; backtrack to 1, then visit 2, 3, ..., 9.

Answer:
[1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]

Complexity comparison:
1. String comparator sort: O(n log n * L) time, O(n) or more auxiliary storage.
2. Sort strings: O(n log n * L) time, O(n * L) space.
3. Recursive DFS: O(n) time, O(log n) call stack (excluding output).
4. Iterative traversal: O(n) time, O(1) auxiliary space (excluding output).

Recommendation:
- If you want to follow the approach you already wrote, use Solution3.
- If you must satisfy the statement's O(1) extra-space requirement, use Solution4.
*/
