/*
LeetCode 3665. Twisted Mirror Path Count
Four C++ approaches: brute DFS, memoized DFS, tabulation, space-optimized DP.

State:
  dir = 0: entered the current cell while moving RIGHT (from its left).
  dir = 1: entered the current cell while moving DOWN (from above).

At an empty cell: choose RIGHT or DOWN.
At a mirror:
  dir 0 (RIGHT-in) -> reflect DOWN.
  dir 1 (DOWN-in)  -> reflect RIGHT.

The start (0,0) is empty. Start with dp[0][0][0] = 1.
Copy one class at a time and rename it to Solution.
*/
#include <bits/stdc++.h>
using namespace std;

class Solution1 {
    static constexpr int MOD = 1'000'000'007;
    int m, n;
    vector<vector<int>>* g;

    int dfs(int i, int j, int dir) {
        if (i >= m || j >= n) return 0;
        if (i == m - 1 && j == n - 1) return 1;

        if ((*g)[i][j] == 1) {
            if (dir == 0) return dfs(i + 1, j, 1);
            return dfs(i, j + 1, 0);
        }

        return (dfs(i, j + 1, 0) + dfs(i + 1, j, 1)) % MOD;
    }

public:
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        g = &grid;
        return dfs(0, 0, 0);
    }
};

/*
Approach 1: Brute-force DFS.
Time: exponential worst case (at most two choices at each empty cell).
Space: O(m+n) recursion depth.
Only for understanding; too slow for m,n <= 500.
*/

class Solution2 {
    static constexpr int MOD = 1'000'000'007;
    int m, n;
    vector<vector<int>>* g;
    vector<vector<array<int, 2>>> memo;

    int dfs(int i, int j, int dir) {
        if (i >= m || j >= n) return 0;
        if (i == m - 1 && j == n - 1) return 1;

        int& ans = memo[i][j][dir];
        if (ans != -1) return ans;

        if ((*g)[i][j] == 1) {
            if (dir == 0) return ans = dfs(i + 1, j, 1);
            return ans = dfs(i, j + 1, 0);
        }

        int right = dfs(i, j + 1, 0);
        int down = dfs(i + 1, j, 1);
        return ans = (right + down) % MOD;
    }

public:
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        g = &grid;
        memo.assign(m, vector<array<int, 2>>(n, array<int, 2>{-1, -1}));
        return dfs(0, 0, 0);
    }
};

/*
Approach 2: Top-down DP (DFS + memoization).
There are only two incoming-direction states per cell.
Time: O(m*n). Space: O(m*n) memo + O(m+n) recursion stack.
This is closest to the recursive solution in the prompt.
*/

class Solution3 {
    static constexpr int MOD = 1'000'000'007;

public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<array<int, 2>>> dp(
            m, vector<array<int, 2>>(n, array<int, 2>{0, 0})
        );

        dp[0][0][0] = 1;

        // Right/down transitions only, so row-major order is topological.
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int fromLeft = dp[i][j][0];
                int fromTop = dp[i][j][1];

                if (i == m - 1 && j == n - 1) continue;

                if (grid[i][j] == 0) {
                    int ways = (fromLeft + fromTop) % MOD;
                    if (j + 1 < n)
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + ways) % MOD;
                    if (i + 1 < m)
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + ways) % MOD;
                } else {
                    // Entered from left -> reflected down.
                    if (i + 1 < m)
                        dp[i + 1][j][1] = (dp[i + 1][j][1] + fromLeft) % MOD;
                    // Entered from top -> reflected right.
                    if (j + 1 < n)
                        dp[i][j + 1][0] = (dp[i][j + 1][0] + fromTop) % MOD;
                }
            }
        }

        return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
    }
};

/*
Approach 3: Bottom-up tabulation.
Time: O(m*n). Space: O(m*n).
*/

class Solution4 {
    static constexpr int MOD = 1'000'000'007;

public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // curr[j]: arrivals at column j in current row.
        // nextRow[j]: arrivals at column j in the following row.
        vector<array<int, 2>> curr(n, array<int, 2>{0, 0});
        vector<array<int, 2>> nextRow(n, array<int, 2>{0, 0});

        curr[0][0] = 1;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int fromLeft = curr[j][0];
                int fromTop = curr[j][1];

                if (i == m - 1 && j == n - 1)
                    return (fromLeft + fromTop) % MOD;

                if (grid[i][j] == 0) {
                    int ways = (fromLeft + fromTop) % MOD;

                    if (j + 1 < n)
                        curr[j + 1][0] = (curr[j + 1][0] + ways) % MOD;
                    if (i + 1 < m)
                        nextRow[j][1] = (nextRow[j][1] + ways) % MOD;
                } else {
                    // RIGHT-in -> DOWN-out.
                    if (i + 1 < m)
                        nextRow[j][1] = (nextRow[j][1] + fromLeft) % MOD;
                    // DOWN-in -> RIGHT-out.
                    if (j + 1 < n)
                        curr[j + 1][0] = (curr[j + 1][0] + fromTop) % MOD;
                }
            }

            curr.swap(nextRow);
            fill(nextRow.begin(), nextRow.end(), array<int, 2>{0, 0});
        }
        return 0;
    }
};

/*
Approach 4: Space-optimized DP.
Time: O(m*n). Auxiliary space: O(n).

Why two states?
A mirror's behavior depends on the direction used to enter it. Counting only
the number of ways to reach a cell loses information and gives wrong answers.

Example 1 result: 5.
Important:
- The start is empty and contributes one initial path.
- A mirror may reflect immediately into another mirror; process that next
  cell normally with the updated direction.
- Reflection outside the grid contributes no path.
- Count both incoming-direction states at the destination.
- Apply modulo after additions.

Recommended:
  Solution2 if you prefer your recursive + memoization style.
  Solution4 for O(m*n) time and O(n) auxiliary space.
*/
