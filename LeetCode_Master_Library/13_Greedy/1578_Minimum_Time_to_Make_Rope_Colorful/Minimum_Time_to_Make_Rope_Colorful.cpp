/*
LeetCode 1578 — Minimum Time to Make Rope Colorful
Original source: Greedy Algorithm/1578. Minimum Time to Make Rope Colorful.cpp
Original source files: 1
Approaches implemented: 4
Recommended: SolutionRunGreedy

Approach index:
1. Exhaustive keep/remove recursion (tiny inputs only)
2. Memoized DP by index and last kept color
3. Bottom-up DP by last kept color
4. Run sum-minus-maximum greedy (recommended)
*/

#include <algorithm>
#include <climits>
#include <string>
#include <vector>
using namespace std;

// 1. Exhaustive recursion.
// Time: O(2^n); auxiliary space: O(n) recursion stack.
// Educational baseline; only for very short strings.
class SolutionBruteForce {
    int dfs(int i, int lastColor, const string& colors,
            const vector<int>& neededTime) {
        if (i == (int)colors.size()) return 0;
        int remove = neededTime[i] +
                     dfs(i + 1, lastColor, colors, neededTime);
        const int color = colors[i] - 'a';
        int keep = INT_MAX / 4;
        if (color != lastColor) {
            keep = dfs(i + 1, color, colors, neededTime);
        }
        return min(remove, keep);
    }

public:
    int minCost(string colors, vector<int>& neededTime) {
        return dfs(0, 26, colors, neededTime);
    }
};

// 2. Memoized DP.
// State: (index, last kept color), with 26 as the empty-prefix sentinel.
// Time: O(27*n); auxiliary space: O(27*n) memo + O(n) recursion.
class SolutionMemoization {
    const string* colors;
    const vector<int>* costs;
    vector<vector<int>> memo;

    int dfs(int i, int lastColor) {
        if (i == (int)colors->size()) return 0;
        int& answer = memo[i][lastColor];
        if (answer != -1) return answer;

        const int remove = (*costs)[i] + dfs(i + 1, lastColor);
        const int color = (*colors)[i] - 'a';
        int keep = INT_MAX / 4;
        if (color != lastColor) keep = dfs(i + 1, color);
        return answer = min(remove, keep);
    }

public:
    int minCost(string c, vector<int>& neededTime) {
        colors = &c;
        costs = &neededTime;
        memo.assign(c.size(), vector<int>(27, -1));
        return dfs(0, 26);
    }
};

// 3. Bottom-up DP by last kept color.
// The state remembers the most recently retained color; this is necessary
// because deleting a balloon can expose an earlier equal-colored balloon.
// Time: O(27*n); auxiliary space: O(27).
class SolutionBottomUpDP {
public:
    int minCost(string colors, vector<int>& neededTime) {
        const long long INF = LLONG_MAX / 4;
        vector<long long> dp(27, INF), next(27, INF);
        dp[26] = 0;

        for (int i = 0; i < (int)colors.size(); ++i) {
            fill(next.begin(), next.end(), INF);
            const int color = colors[i] - 'a';
            for (int last = 0; last <= 26; ++last) {
                if (dp[last] == INF) continue;

                next[last] = min(next[last],
                                 dp[last] + neededTime[i]);
                if (last != color) {
                    next[color] = min(next[color], dp[last]);
                }
            }
            dp.swap(next);
        }
        return (int)*min_element(dp.begin(), dp.end());
    }
};

// 4. Scan maximal same-color runs; remove every cost except the maximum.
// Time: O(n); auxiliary space: O(1). Does not modify neededTime.
class SolutionRunGreedy {
public:
    int minCost(string colors, vector<int>& neededTime) {
        long long answer = 0;
        for (int i = 0, n = (int)colors.size(); i < n;) {
            int j = i;
            long long sum = 0;
            int maximum = 0;
            while (j < n && colors[j] == colors[i]) {
                sum += neededTime[j];
                maximum = max(maximum, neededTime[j]);
                ++j;
            }
            answer += sum - maximum;
            i = j;
        }
        return (int)answer;
    }
};
