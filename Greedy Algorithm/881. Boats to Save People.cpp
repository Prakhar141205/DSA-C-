/*
LeetCode 881 — Boats to Save People
Comprehensive C++ solution variations

Problem:
Each boat carries at most two people, and the total weight on a boat must
not exceed `limit`. Return the minimum number of boats.

CORE GREEDY INSIGHT
Sort people by weight. Let:
- i = lightest person not yet assigned
- j = heaviest person not yet assigned

The heaviest remaining person must use a boat now. Pair that person with the
lightest remaining person if their combined weight fits. If they do not fit,
the heaviest person must travel alone: even the lightest remaining person
cannot share with them.

This gives the optimal two-pointer greedy algorithm.

Included approaches:
1. Brute-force recursive assignment / pairing (exponential).
2. Memoized bitmask DP (exponential; small n only).
3. Bottom-up bitmask DP (exponential; small n only).
4. Sort + two pointers (canonical optimal greedy).
5. Sort + deque (same greedy, different container).
6. Multiset greedy (same greedy, O(n log n)).
7. Counting sort + two pointers (uses bounded weight constraint).
8. Frequency-array greedy directly (avoids comparison sort).

For the original constraints n <= 50,000 and limit <= 30,000, use #4 or #8.
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------------------------------
// 1. BRUTE FORCE RECURSION
// Pick the first person who has not been assigned.
// Try putting them alone, or pair them with each other unassigned person if
// the pair fits. Return the minimum boats.
// Time: exponential (roughly O((n-1)!!)-scale pairing exploration).
// Space: O(n) recursion depth.
// Only for tiny n; no memoization.
// -----------------------------------------------------------------------------
class Solution1_BruteForce {
    int n;

    int dfs(const vector<int>& people, int mask, int usedCount, int limit) {
        if (usedCount == n) return 0;

        int i = 0;
        while (mask & (1 << i)) ++i;

        // Option A: person i goes alone.
        int best = 1 + dfs(people, mask | (1 << i),
                          usedCount + 1, limit);

        // Option B: person i shares with any unassigned person j.
        for (int j = i + 1; j < n; ++j) {
            if ((mask & (1 << j)) == 0 &&
                people[i] + people[j] <= limit) {
                best = min(best,
                    1 + dfs(people, mask | (1 << i) | (1 << j),
                            usedCount + 2, limit));
            }
        }

        return best;
    }

public:
    int numRescueBoats(vector<int>& people, int limit) {
        n = (int)people.size();
        // Bitmask is only safe for small n in this teaching implementation.
        if (n > 20) return -1;
        return dfs(people, 0, 0, limit);
    }
};

// -----------------------------------------------------------------------------
// 2. MEMOIZED BITMASK DP
// Same recurrence as #1, but cache the answer for each used-person mask.
// Time: O(2^n * n) upper bound.
// Space: O(2^n).
// Only for small n (typically n <= 20).
// -----------------------------------------------------------------------------
class Solution2_MemoizedBitmaskDP {
    vector<int> memo;
    int n;

    int dfs(const vector<int>& people, int mask, int limit) {
        if (mask == (1 << n) - 1) return 0;
        int& ans = memo[mask];
        if (ans != -1) return ans;

        int i = 0;
        while (mask & (1 << i)) ++i;

        ans = 1 + dfs(people, mask | (1 << i), limit);

        for (int j = i + 1; j < n; ++j) {
            if (!(mask & (1 << j)) &&
                people[i] + people[j] <= limit) {
                ans = min(ans, 1 + dfs(
                    people, mask | (1 << i) | (1 << j), limit));
            }
        }

        return ans;
    }

public:
    int numRescueBoats(vector<int>& people, int limit) {
        n = (int)people.size();
        if (n > 20) return -1;
        memo.assign(1 << n, -1);
        return dfs(people, 0, limit);
    }
};

// -----------------------------------------------------------------------------
// 3. BOTTOM-UP BITMASK DP
// dp[mask] = minimum boats needed to transport exactly the people in `mask`.
// Add one unused person alone or add a valid pair.
// Time: O(2^n * n^2) in this direct formulation.
// Space: O(2^n).
// Exponential; included as a standard iterative DP variation.
// -----------------------------------------------------------------------------
class Solution3_BottomUpBitmaskDP {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = (int)people.size();
        if (n > 20) return -1;

        const int FULL = (1 << n) - 1;
        const int INF = n + 1;
        vector<int> dp(1 << n, INF);
        dp[0] = 0;

        for (int mask = 0; mask <= FULL; ++mask) {
            if (dp[mask] == INF) continue;

            int i = 0;
            while (i < n && (mask & (1 << i))) ++i;
            if (i == n) continue;

            int maskAlone = mask | (1 << i);
            dp[maskAlone] = min(dp[maskAlone], dp[mask] + 1);

            for (int j = i + 1; j < n; ++j) {
                if (!(mask & (1 << j)) &&
                    people[i] + people[j] <= limit) {
                    int nextMask = mask | (1 << i) | (1 << j);
                    dp[nextMask] = min(dp[nextMask], dp[mask] + 1);
                }
            }
        }

        return dp[FULL];
    }
};

// -----------------------------------------------------------------------------
// 4. SORT + TWO POINTERS — CANONICAL OPTIMAL GREEDY
// Time: O(n log n) for sorting + O(n) scan.
// Space: O(1) auxiliary apart from sorting implementation details.
// -----------------------------------------------------------------------------
class Solution4_TwoPointers {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int i = 0;
        int j = (int)people.size() - 1;
        int boats = 0;

        while (i <= j) {
            if (i < j && people[i] + people[j] <= limit) {
                // Lightest and heaviest share one boat.
                ++i;
                --j;
            } else {
                // Heaviest must go alone.
                --j;
            }
            ++boats;
        }

        return boats;
    }
};

// -----------------------------------------------------------------------------
// 5. SORT + DEQUE
// Same greedy decisions as #4. The smallest is at the front and largest at
// the back.
// Time: O(n log n), Space: O(n) for the deque copy.
// -----------------------------------------------------------------------------
class Solution5_Deque {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        deque<int> dq(people.begin(), people.end());

        int boats = 0;
        while (!dq.empty()) {
            int heaviest = dq.back();
            dq.pop_back();

            if (!dq.empty() && dq.front() + heaviest <= limit) {
                dq.pop_front();
            }

            ++boats;
        }

        return boats;
    }
};

// -----------------------------------------------------------------------------
// 6. MULTISET GREEDY
// Repeatedly take the largest person; pair with the smallest if possible.
// Time: O(n log n), Space: O(n).
// -----------------------------------------------------------------------------
class Solution6_Multiset {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        multiset<int> remaining(people.begin(), people.end());
        int boats = 0;

        while (!remaining.empty()) {
            auto heaviestIt = prev(remaining.end());
            int heaviest = *heaviestIt;
            remaining.erase(heaviestIt);

            if (!remaining.empty() &&
                *remaining.begin() + heaviest <= limit) {
                remaining.erase(remaining.begin());
            }

            ++boats;
        }

        return boats;
    }
};

// -----------------------------------------------------------------------------
// 7. COUNTING SORT + TWO POINTERS
// Constraint: 1 <= people[i] <= limit <= 30000.
// Build the sorted sequence in O(n + limit), then use the two-pointer greedy.
// Time: O(n + limit), Space: O(n + limit).
// This can outperform comparison sorting when the value range is small.
// -----------------------------------------------------------------------------
class Solution7_CountingSort {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        vector<int> freq(limit + 1, 0);
        for (int w : people) ++freq[w];

        vector<int> sorted;
        sorted.reserve(people.size());

        for (int w = 1; w <= limit; ++w) {
            while (freq[w] > 0) {
                sorted.push_back(w);
                --freq[w];
            }
        }

        int i = 0;
        int j = (int)sorted.size() - 1;
        int boats = 0;

        while (i <= j) {
            if (i < j && sorted[i] + sorted[j] <= limit) {
                ++i;
                --j;
            } else {
                --j;
            }
            ++boats;
        }

        return boats;
    }
};

// -----------------------------------------------------------------------------
// 8. FREQUENCY-ARRAY GREEDY WITHOUT BUILDING A SORTED VECTOR
// Store counts by weight. Maintain pointers to the lightest and heaviest
// remaining weights. Each boat removes the heaviest; if possible, also remove
// the lightest.
// Time: O(n + limit), Space: O(limit).
// Exploits the bounded weight constraint directly.
// -----------------------------------------------------------------------------
class Solution8_FrequencyTwoPointers {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        vector<int> freq(limit + 1, 0);
        for (int w : people) ++freq[w];

        int light = 1;
        int heavy = limit;
        int remaining = (int)people.size();
        int boats = 0;

        while (remaining > 0) {
            while (light <= limit && freq[light] == 0) ++light;
            while (heavy >= 1 && freq[heavy] == 0) --heavy;

            // The heaviest remaining person always boards this boat.
            --freq[heavy];
            --remaining;

            // Pair with the lightest remaining person if they fit.
            while (light <= limit && freq[light] == 0) ++light;
            if (remaining > 0 && light <= limit &&
                light + heavy <= limit) {
                --freq[light];
                --remaining;
            }

            ++boats;
        }

        return boats;
    }
};

/*
CORRECTNESS INTUITION FOR THE GREEDY
Consider the heaviest remaining person H.
- H must be assigned to some boat.
- If the lightest remaining person L satisfies L + H <= limit, pairing L
  with H is safe: pairing H with any heavier person would be no easier, and
  L is the person most likely to fit. An exchange argument can replace the
  partner of H with L without increasing the number of boats.
- If L + H > limit, then H cannot share with anyone remaining, so H must
  occupy a boat alone.

Repeating this choice yields an optimal assignment.

IMPORTANT ISSUE IN THE USER'S CODE
Your condition:
    if (i + 1 < n && people[i] + people[j] <= limit)
should be:
    if (i < j && people[i] + people[j] <= limit)

Reason: `i < j` ensures that two distinct people are paired. The check
`i + 1 < n` only checks whether i is before the original last index; it does
not ensure that i and j are different. Your accepted implementation still
gets the correct count in the shown tests, but the condition should express
the actual invariant.

Recommended code:
    class Solution {
    public:
        int numRescueBoats(vector<int>& people, int limit) {
            sort(people.begin(), people.end());

            int i = 0, j = (int)people.size() - 1;
            int boats = 0;

            while (i <= j) {
                if (i < j && people[i] + people[j] <= limit) {
                    ++i;
                    --j;
                } else {
                    --j;
                }
                ++boats;
            }
            return boats;
        }
    };

COMPLEXITY SUMMARY
1. Brute-force recursion       Exponential       O(n) recursion
2. Memoized bitmask DP         O(2^n * n)        O(2^n)
3. Bottom-up bitmask DP        O(2^n * n^2)      O(2^n)
4. Sort + two pointers          O(n log n)        O(1) auxiliary*
5. Sort + deque                 O(n log n)        O(n)
6. Multiset                     O(n log n)        O(n)
7. Counting sort + two pointers O(n + limit)      O(n + limit)
8. Frequency two pointers       O(n + limit)      O(limit)

*Sorting may use implementation-dependent stack space.

BEST CHOICE
- Interview / standard solution: #4 (sort + two pointers).
- If specifically exploiting the given small weight bound: #8 (frequency array).
- For n up to 50,000, do not use the exponential DP approaches.
*/
