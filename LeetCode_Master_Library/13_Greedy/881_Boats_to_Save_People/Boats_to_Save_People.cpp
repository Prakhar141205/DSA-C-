/*
LeetCode 881 — Boats to Save People
Original source: Greedy Algorithm/881. Boats to Save People.cpp
Original source files: 1
Approaches implemented: 5
Recommended: SolutionSortTwoPointers

Approach index:
1. Exhaustive recursive assignment (tiny inputs only)
2. Top-down bitmask DP (tiny inputs only)
3. Bottom-up bitmask DP (tiny inputs only)
4. Sort + two-pointer greedy (recommended general solution)
5. Frequency array + two pointers (uses the bounded weight constraint)
*/

#include <algorithm>
#include <climits>
#include <functional>
#include <vector>
using namespace std;

// 1. Exhaustive recursion.
// Time: exponential; at most O(n!) explored assignment orderings.
// Auxiliary space: O(n) recursion depth.
// Use only for tiny n. This avoids bit shifts but remains impractical.
class SolutionBruteForce {
    int dfs(const vector<int>& people, vector<char>& used, int remaining,
            int limit) {
        if (remaining == 0) return 0;

        int first = 0;
        while (used[first]) ++first;

        used[first] = true;
        int best = 1 + dfs(people, used, remaining - 1, limit);

        for (int partner = first + 1; partner < (int)people.size(); ++partner) {
            if (!used[partner] &&
                (long long)people[first] + people[partner] <= limit) {
                used[partner] = true;
                best = min(best, 1 + dfs(people, used, remaining - 2, limit));
                used[partner] = false;
            }
        }

        used[first] = false;
        return best;
    }

public:
    int numRescueBoats(vector<int>& people, int limit) {
        vector<char> used(people.size(), false);
        return dfs(people, used, (int)people.size(), limit);
    }
};

// 2. Top-down bitmask DP.
// State: mask is the set of people already assigned.
// Time: O(2^n * n); auxiliary space: O(2^n) memo + O(n) stack.
// Use only for small n (e.g. n <= 20); exponential memory is not suitable
// for the original maximum n of 50,000.
class SolutionMemoization {
    int n;
    vector<int> memo;

    int dfs(const vector<int>& people, int mask, int limit) {
        if (mask == (1 << n) - 1) return 0;

        int& answer = memo[mask];
        if (answer != -1) return answer;

        int first = 0;
        while (mask & (1 << first)) ++first;

        answer = 1 + dfs(people, mask | (1 << first), limit);
        for (int partner = first + 1; partner < n; ++partner) {
            if (!(mask & (1 << partner)) &&
                (long long)people[first] + people[partner] <= limit) {
                answer = min(answer,
                             1 + dfs(people, mask | (1 << first) |
                                                 (1 << partner),
                                     limit));
            }
        }
        return answer;
    }

public:
    int numRescueBoats(vector<int>& people, int limit) {
        n = (int)people.size();
        if (n == 0) return 0;
        if (n > 20) return -1;
        memo.assign(1 << n, -1);
        return dfs(people, 0, limit);
    }
};

// 3. Bottom-up bitmask DP.
// dp[mask] is the fewest boats needed to assign exactly mask.
// Time: O(2^n * n); auxiliary space: O(2^n).
// Suitable only for small n; included to show iterative evaluation of the
// same state graph as SolutionMemoization.
class SolutionBottomUpBitmaskDP {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        const int n = (int)people.size();
        if (n == 0) return 0;
        if (n > 20) return -1;

        const int states = 1 << n;
        const int full = states - 1;
        vector<int> dp(states, n + 1);
        dp[0] = 0;

        for (int mask = 0; mask < states; ++mask) {
            if (dp[mask] == n + 1 || mask == full) continue;

            int first = 0;
            while (mask & (1 << first)) ++first;

            const int alone = mask | (1 << first);
            dp[alone] = min(dp[alone], dp[mask] + 1);

            for (int partner = first + 1; partner < n; ++partner) {
                if (!(mask & (1 << partner)) &&
                    (long long)people[first] + people[partner] <= limit) {
                    const int paired =
                        mask | (1 << first) | (1 << partner);
                    dp[paired] = min(dp[paired], dp[mask] + 1);
                }
            }
        }
        return dp[full];
    }
};

// 4. Sort + two-pointer greedy.
// Time: O(n log n) for sorting + O(n) scan.
// Auxiliary space: O(log n) implementation-dependent sorting stack;
// the scan itself uses O(1). This sorts and therefore mutates people.
class SolutionSortTwoPointers {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int light = 0;
        int heavy = (int)people.size() - 1;
        int boats = 0;

        while (light <= heavy) {
            if (light < heavy &&
                (long long)people[light] + people[heavy] <= limit) {
                ++light;
            }
            --heavy;
            ++boats;
        }
        return boats;
    }
};

// 5. Frequency array + two pointers.
// Constraint-specific: 1 <= people[i] <= limit <= 30,000.
// Time: O(n + limit); auxiliary space: O(limit).
// Unlike the sorting solution, this uses the small bounded integer domain.
class SolutionFrequencyArray {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        vector<int> frequency(limit + 1, 0);
        for (int weight : people) ++frequency[weight];

        int light = 1;
        int heavy = limit;
        int remaining = (int)people.size();
        int boats = 0;

        while (remaining > 0) {
            while (light <= limit && frequency[light] == 0) ++light;
            while (heavy >= 1 && frequency[heavy] == 0) --heavy;

            --frequency[heavy];
            --remaining;

            while (light <= limit && frequency[light] == 0) ++light;
            if (remaining > 0 && light <= limit &&
                light + heavy <= limit) {
                --frequency[light];
                --remaining;
            }
            ++boats;
        }
        return boats;
    }
};
