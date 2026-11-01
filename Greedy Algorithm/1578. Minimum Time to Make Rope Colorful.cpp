/*
LeetCode 1578 — Minimum Time to Make Rope Colorful
Comprehensive C++ solution variations

KEY OBSERVATION
Only maximal contiguous runs of equal colors create conflicts.
For a run with removal costs t1...tk, at most one balloon may remain.
Keep the balloon with maximum removal cost; remove the rest.
Run cost = sum(run costs) - max(run costs).

Included:
1. Brute-force recursion.
2. Memoized DP: (index, last kept color).
3. Bottom-up DP over last kept color.
4. Two-state DP: keep/remove current balloon.
5. Adjacent-pair greedy (the user's approach).
6. One-pass group sum-minus-maximum greedy.
7. Stack-based conflict resolution.
8. Sort each equal-color run and remove all but its maximum.

#1 is exponential. #2–#3 are O(26*n) / O(26) or O(26*n) space.
#4–#8 are polynomial; #5 and #6 are O(n) time and O(1) auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

// 1. BRUTE FORCE RECURSION — O(2^n) time, O(n) recursion stack.
class Solution1_BruteForce {
    int n;
    string colors;
    vector<int> cost;

    int dfs(int i, int lastColor) {
        if (i == n) return 0;

        int removeCurrent = cost[i] + dfs(i + 1, lastColor);

        int keepCurrent = INT_MAX / 2;
        int c = colors[i] - 'a';
        if (c != lastColor) keepCurrent = dfs(i + 1, c);

        return min(removeCurrent, keepCurrent);
    }

public:
    int minCost(string c, vector<int>& neededTime) {
        colors = move(c);
        cost = neededTime;
        n = (int)colors.size();
        return dfs(0, 26); // 26 means no previous balloon was kept.
    }
};

// 2. TOP-DOWN MEMOIZED DP — O(27*n) time, O(27*n) memo + O(n) stack.
class Solution2_MemoizedDP {
    int n;
    string colors;
    vector<int> cost;
    vector<vector<int>> memo;

    int dfs(int i, int lastColor) {
        if (i == n) return 0;
        int& ans = memo[i][lastColor];
        if (ans != -1) return ans;

        int removeCurrent = cost[i] + dfs(i + 1, lastColor);
        int keepCurrent = INT_MAX / 2;
        int c = colors[i] - 'a';

        if (c != lastColor) keepCurrent = dfs(i + 1, c);
        return ans = min(removeCurrent, keepCurrent);
    }

public:
    int minCost(string c, vector<int>& neededTime) {
        colors = move(c);
        cost = neededTime;
        n = (int)colors.size();
        memo.assign(n, vector<int>(27, -1));
        return dfs(0, 26);
    }
};

// 3. BOTTOM-UP LAST-KEPT-COLOR DP — O(27*26*n) time, O(27) space.
// dp[last] = minimum cost for the processed prefix, with `last` as the
// color of the last retained balloon; 26 is the empty state.
class Solution3_BottomUpColorDP {
public:
    int minCost(string colors, vector<int>& neededTime) {
        const int INF = INT_MAX / 4;
        vector<int> dp(27, INF), ndp(27, INF);
        dp[26] = 0;

        for (int i = 0; i < (int)colors.size(); ++i) {
            fill(ndp.begin(), ndp.end(), INF);
            int c = colors[i] - 'a';

            for (int last = 0; last <= 26; ++last) {
                if (dp[last] == INF) continue;

                // Remove this balloon.
                ndp[last] = min(ndp[last], dp[last] + neededTime[i]);

                // Keep this balloon if it differs from the last kept color.
                if (last != c) ndp[c] = min(ndp[c], dp[last]);
            }
            dp.swap(ndp);
        }

        return *min_element(dp.begin(), dp.end());
    }
};

// 4. TWO-STATE DP — O(n) time, O(n) space.
// keep[i]: minimum cost through i when i is retained.
// remove[i]: minimum cost through i when i is removed.
class Solution4_TwoStateDP {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = (int)colors.size();
        if (n <= 1) return 0;

        vector<int> keep(n, 0), remove(n, 0);
        remove[0] = neededTime[0];

        for (int i = 1; i < n; ++i) {
            int bestPrev = min(keep[i - 1], remove[i - 1]);

            if (colors[i] != colors[i - 1]) {
                keep[i] = bestPrev;
            } else {
                // Same color: if i is kept, i-1 must be removed.
                keep[i] = remove[i - 1];
            }

            remove[i] = bestPrev + neededTime[i];
        }

        return min(keep[n - 1], remove[n - 1]);
    }
};

// 5. ADJACENT-PAIR GREEDY — O(n) time, O(1) auxiliary space.
// This is the user's approach. Carry the maximum removal cost in each run.
class Solution5_AdjacentPairGreedy {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int answer = 0;
        for (int i = 0; i + 1 < (int)colors.size(); ++i) {
            if (colors[i] == colors[i + 1]) {
                answer += min(neededTime[i], neededTime[i + 1]);
                neededTime[i + 1] = max(neededTime[i], neededTime[i + 1]);
            }
        }
        return answer;
    }
};

// 6. GROUP SCAN: sum - maximum — O(n) time, O(1) auxiliary space.
// Does not modify the input vector.
class Solution6_GroupSumMinusMax {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = (int)colors.size();
        int answer = 0;
        int i = 0;

        while (i < n) {
            int j = i;
            int sum = 0, mx = 0;

            while (j < n && colors[j] == colors[i]) {
                sum += neededTime[j];
                mx = max(mx, neededTime[j]);
                ++j;
            }

            answer += sum - mx;
            i = j;
        }
        return answer;
    }
};

// 7. STACK-BASED CONFLICT RESOLUTION — O(n) time, O(n) space.
// Store one surviving representative per processed run.
class Solution7_Stack {
public:
    int minCost(string colors, vector<int>& neededTime) {
        vector<pair<char, int>> st;
        int answer = 0;

        for (int i = 0; i < (int)colors.size(); ++i) {
            if (!st.empty() && st.back().first == colors[i]) {
                if (st.back().second <= neededTime[i]) {
                    answer += st.back().second;
                    st.back().second = neededTime[i];
                } else {
                    answer += neededTime[i];
                }
            } else {
                st.push_back({colors[i], neededTime[i]});
            }
        }
        return answer;
    }
};

// 8. SORT EACH RUN — O(n log n) worst-case time, O(n) space.
class Solution8_SortEachRun {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = (int)colors.size();
        int answer = 0;
        int i = 0;

        while (i < n) {
            int j = i;
            vector<int> run;
            while (j < n && colors[j] == colors[i]) {
                run.push_back(neededTime[j]);
                ++j;
            }

            sort(run.begin(), run.end());
            for (int k = 0; k + 1 < (int)run.size(); ++k) {
                answer += run[k];
            }
            i = j;
        }
        return answer;
    }
};

/*
DRY RUN
colors = "abaac", neededTime = [1,2,3,4,5]
Runs:
"a"  -> 1 - 1 = 0
"b"  -> 2 - 2 = 0
"aa" -> (3 + 4) - 4 = 3
"c"  -> 5 - 5 = 0
Answer = 3.

WHY KEEP THE MAXIMUM?
A contiguous run of k equal-colored balloons can retain at most one balloon.
Every removal has a positive cost, so retaining the balloon with the largest
removal time minimizes the total removal cost.

USER CODE REVIEW
Your adjacent-pair approach is correct:
    answer += min(neededTime[i], neededTime[i + 1]);
    neededTime[i + 1] = max(neededTime[i], neededTime[i + 1]);

The update propagates the maximum cost through a run. For costs [3,5,10]:
- remove min(3,5) = 3, carry 5
- remove min(5,10) = 5, carry 10
Total removed = 8 = 3+5+10-10.

Remove the debug cout. Use Solution6 if you do not want to mutate neededTime.

COMPLEXITY SUMMARY
1. Brute-force recursion       O(2^n)       O(n) stack
2. Memoized color DP           O(27*n)      O(27*n) + stack
3. Bottom-up color DP          O(27*26*n)   O(27)
4. Two-state DP                O(n)         O(n)
5. Adjacent-pair greedy        O(n)         O(1)
6. Group sum - maximum          O(n)         O(1)
7. Stack greedy                O(n)         O(n)
8. Sort each run               O(n log n)   O(n)

RECOMMENDATION
- Best interview explanation: #6, group sum minus maximum.
- Best compact in-place greedy: #5, your approach.
- Best DP practice: #2 or #4.
*/
