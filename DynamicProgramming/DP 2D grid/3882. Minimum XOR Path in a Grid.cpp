

/******************************************************* C++ *******************************************************/
//Approach (Bits Xor Property and Grid DP format)
//T.C : O(m*n)
//S.C : O(m*n)
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<bitset<1024>>> dp(m, vector<bitset<1024>>(n));
        //m*n
        //dp[i][j] = it stores a bitset<1024> {0, 0, 1, 1, 0, .....}

        dp[0][0][grid[0][0]] = 1;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(i == 0 && j == 0)
                    continue;

                bitset<1024> up; //[i-1][j]
                bitset<1024> left; //[i][j-1]

                if(i > 0) {
                    up = dp[i-1][j];
                }
                if(j > 0) {
                    left = dp[i][j-1];
                }

                bitset<1024> combined = up | left; //OR operation

                for(int xorVal = 0; xorVal < 1024; xorVal++) {
                    if(combined[xorVal]) {
                        int resultXorVal = xorVal ^ grid[i][j];
                        dp[i][j][resultXorVal] = 1;
                    }
                }
            }
        }

        //dp[m-1][n-1]
        for(int xorVal = 0; xorVal < 1024; xorVal++) {
            if(dp[m-1][n-1][xorVal]) {
                return xorVal;
            }
        }

        return -1;

        
    }
};

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();

        vector<array<bool, 1024>> dp(n);
        array<bool, 1024> next{};

        dp[0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }

                const int value = grid[i][j];
                next.fill(false);

                for (int k = 0; k < 1024; k++) {
                    if (dp[j][k] || (j > 0 && dp[j - 1][k])) {
                        next[k ^ value] = true;
                    }
                }

                dp[j] = next;
            }
        }

        for (int k = 0; k < 1024; k++) {
            if (dp[n - 1][k]) {
                return k;
            }
        }

        return -1;
    }
};


/*
  Minimum XOR value on a path from grid[0][0] to grid[m-1][n-1].
  Moves allowed: right or down. Assumption: every cell value < 1024.

  Approaches:
  1. Brute-force DFS
  2. Memoized DFS / reachable states
  3. 3D Boolean DP
  4. 2D bitset DP (the supplied approach)
  5. Set-based DP
  6. Top-down bitset DP
  7. Space-optimized bitset DP

  V = 1024 possible XOR values.
*/
#include <bits/stdc++.h>
using namespace std;
static constexpr int V = 1024;

// 1. Brute-force DFS: enumerate every right/down path.
// Time: O(number of paths), upper-bounded by O(2^(m+n)); space O(m+n).
class SolutionBruteForce {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), ans = INT_MAX;
        function<void(int,int,int)> dfs = [&](int r, int c, int x) {
            x ^= grid[r][c];
            if (r == m-1 && c == n-1) {
                ans = min(ans, x);
                return;
            }
            if (r+1 < m) dfs(r+1, c, x);
            if (c+1 < n) dfs(r, c+1, x);
        };
        dfs(0, 0, 0);
        return ans;
    }
};

// 2. Memoized traversal: each (row, col, XOR-so-far) state is processed once.
// Time O(m*n*V); space O(m*n*V).
class SolutionMemoizedDFS {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<char>>> seen(
            m, vector<vector<char>>(n, vector<char>(V, false)));

        function<void(int,int,int)> dfs = [&](int r, int c, int x) {
            x ^= grid[r][c];
            if (seen[r][c][x]) return;
            seen[r][c][x] = true;
            if (r+1 < m) dfs(r+1, c, x);
            if (c+1 < n) dfs(r, c+1, x);
        };
        dfs(0, 0, 0);

        for (int x = 0; x < V; ++x)
            if (seen[m-1][n-1][x]) return x;
        return -1;
    }
};

// 3. 3D Boolean DP: dp[r][c][x] means XOR x can reach cell (r,c).
// Time O(m*n*V); space O(m*n*V) bytes approximately.
class Solution3DBooleanDP {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<char>>> dp(
            m, vector<vector<char>>(n, vector<char>(V, false)));
        dp[0][0][grid[0][0]] = true;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 && c == 0) continue;
                if (r > 0) {
                    for (int x = 0; x < V; ++x)
                        if (dp[r-1][c][x]) dp[r][c][x ^ grid[r][c]] = true;
                }
                if (c > 0) {
                    for (int x = 0; x < V; ++x)
                        if (dp[r][c-1][x]) dp[r][c][x ^ grid[r][c]] = true;
                }
            }
        }
        for (int x = 0; x < V; ++x)
            if (dp[m-1][n-1][x]) return x;
        return -1;
    }
};

// 4. 2D bitset DP: one bit represents reachability of one XOR value.
// Time O(m*n*V); space O(m*n*V) bits.
class SolutionBitsetDP {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bitset<V>>> dp(m, vector<bitset<V>>(n));
        dp[0][0][grid[0][0]] = true;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 && c == 0) continue;
                bitset<V> combined;
                if (r > 0) combined |= dp[r-1][c];
                if (c > 0) combined |= dp[r][c-1];

                for (int x = 0; x < V; ++x)
                    if (combined[x]) dp[r][c][x ^ grid[r][c]] = true;
            }
        }
        for (int x = 0; x < V; ++x)
            if (dp[m-1][n-1][x]) return x;
        return -1;
    }
};

// 5. Set-based DP: store only reachable XOR values at each cell.
// Expected time O(m*n*V) worst case; space O(m*n*V) worst case.
class SolutionSetDP {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<unordered_set<int>>> dp(
            m, vector<unordered_set<int>>(n));
        dp[0][0].insert(grid[0][0]);

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 && c == 0) continue;
                auto transfer = [&](const unordered_set<int>& prev) {
                    for (int x : prev) dp[r][c].insert(x ^ grid[r][c]);
                };
                if (r > 0) transfer(dp[r-1][c]);
                if (c > 0) transfer(dp[r][c-1]);
            }
        }
        int ans = INT_MAX;
        for (int x : dp[m-1][n-1]) ans = min(ans, x);
        return ans == INT_MAX ? -1 : ans;
    }
};

// 6. Top-down bitset DP: solve(r,c) returns possible suffix XORs from
// (r,c) to the destination, including grid[r][c].
// Time O(m*n*V); space O(m*n*V) bits plus recursion stack.
class SolutionTopDownBitsetDP {
    int m, n;
    vector<vector<bitset<V>>> memo;
    vector<vector<char>> done;
    vector<vector<int>>* g;

    bitset<V> solve(int r, int c) {
        if (done[r][c]) return memo[r][c];
        done[r][c] = true;

        bitset<V> suffix;
        if (r == m-1 && c == n-1) {
            suffix[0] = true; // empty suffix beyond destination
        } else {
            if (r+1 < m) suffix |= solve(r+1, c);
            if (c+1 < n) suffix |= solve(r, c+1);
        }

        bitset<V> result;
        for (int x = 0; x < V; ++x)
            if (suffix[x]) result[x ^ (*g)[r][c]] = true;
        return memo[r][c] = result;
    }

public:
    int minCost(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size(); g = &grid;
        memo.assign(m, vector<bitset<V>>(n));
        done.assign(m, vector<char>(n, false));
        bitset<V> possible = solve(0, 0);
        for (int x = 0; x < V; ++x) if (possible[x]) return x;
        return -1;
    }
};

// 7. Space-optimized bitset DP: retain only one row.
// Before updating dp[c], it is the state from above; dp[c-1] is from left.
// Time O(m*n*V); space O(n*V) bits.
class SolutionSpaceOptimizedBitsetDP {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<bitset<V>> dp(n);

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r == 0 && c == 0) {
                    dp[c].reset();
                    dp[c][grid[r][c]] = true;
                    continue;
                }
                bitset<V> combined = dp[c]; // from above
                if (c > 0) combined |= dp[c-1]; // from left
                bitset<V> current;
                for (int x = 0; x < V; ++x)
                    if (combined[x]) current[x ^ grid[r][c]] = true;
                dp[c] = current;
            }
        }
        for (int x = 0; x < V; ++x)
            if (dp[n-1][x]) return x;
        return -1;
    }
};

/*
Complexity table (V = 1024)
+------------------------------+----------------------+----------------------+
| Approach                     | Time                 | Auxiliary space      |
+------------------------------+----------------------+----------------------+
| 1. Brute-force DFS           | O(number of paths)   | O(m+n)               |
| 2. Memoized traversal        | O(m*n*V)             | O(m*n*V)              |
| 3. 3D Boolean DP             | O(m*n*V)             | O(m*n*V) bytes        |
| 4. 2D bitset DP              | O(m*n*V)             | O(m*n*V) bits         |
| 5. Set-based DP              | O(m*n*V) worst case  | O(m*n*V) worst case   |
| 6. Top-down bitset DP        | O(m*n*V)             | O(m*n*V) bits         |
| 7. Space-optimized bitset DP | O(m*n*V)             | O(n*V) bits           |
+------------------------------+----------------------+----------------------+

Recommended: Approach 1 for intuition, Approach 3 for standard DP,
Approach 4 for your bitset technique, and Approach 7 to reduce memory.

Assumption: all grid values and path XORs are in [0, 1023]. Increase V or
change the representation if the actual problem has larger values.
*/
