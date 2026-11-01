/*
    LeetCode 2136 — Earliest Possible Day of Full Bloom
    Difficulty: Hard
    Topic: Greedy, Sorting, Scheduling

    Problem:
      Each seed i requires plantTime[i] units of single-worker planting time,
      followed by growTime[i] units of independent growth time.
      Only one seed can be planted at a time, but growth happens in parallel.
      Minimize the day on which every seed has bloomed.

    Key scheduling model:
      If seed i finishes planting at time C_i, it blooms at C_i + growTime[i].
      We must minimize max_i(C_i + growTime[i]).

    Meaningful approaches included:
      1. Brute force over all planting permutations — O(n! * n)
      2. Subset DP over sets of already-planted seeds — O(n * 2^n)
      3. Greedy by descending growTime using comparison sort — O(n log n)
      4. Greedy by descending growTime using selection — O(n^2)

    The first two are educational exact baselines and are not feasible for
    the maximum constraint n = 100,000. The comparison-sort greedy is optimal.

    All implementations use the original LeetCode function signature.
*/

class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();

        vector<pair<int, int>> vec(n);
        for(int i=0; i<n; i++){

            vec[i] = {plantTime[i], growTime[i]};
        }

        sort(begin(vec), end(vec), [](auto p1, auto p2) {
            return p1.second > p2.second;
        });

        int maxBloomDays = 0;
        int prevPlantdays = 0;

        for(int i=0; i<n; i++ ) {
            int currPlantTime = vec[i].first;
            int currGrowtime = vec[i].second;

            prevPlantdays += currPlantTime ;
            int currBloomTime = prevPlantdays + currGrowtime;
            maxBloomDays = max(maxBloomDays, currBloomTime);
        }

        return maxBloomDays;
    }
};

#include <algorithm>
#include <climits>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

// -----------------------------------------------------------------------------
// 1. BRUTE FORCE: TRY EVERY POSSIBLE PLANTING ORDER
// -----------------------------------------------------------------------------
// Intuition:
//   The planting order determines each seed's planting completion time.
//   Enumerate every permutation, calculate the last bloom time for that order,
//   and return the minimum.
//
// Complexity:
//   Time:  O(n! * n) — n! orders, and O(n) work to evaluate each order.
//   Space: O(n)      — recursion stack and the used[] array.
//
// Practicality:
//   Only useful for very small n. It is an exact baseline for validating
//   optimized approaches on tiny inputs.

class SolutionBruteForce {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        const int n = static_cast<int>(plantTime.size());
        vector<bool> used(n, false);
        long long answer = LLONG_MAX;

        function<void(int, long long, long long)> dfs =
            [&](int plantedCount, long long currentDay, long long latestBloom) {
                if (plantedCount == n) {
                    answer = min(answer, latestBloom);
                    return;
                }

                for (int i = 0; i < n; ++i) {
                    if (used[i]) continue;

                    used[i] = true;
                    long long finishPlanting = currentDay + plantTime[i];
                    long long bloomDay = finishPlanting + growTime[i];

                    dfs(plantedCount + 1,
                        finishPlanting,
                        max(latestBloom, bloomDay));

                    used[i] = false;
                }
            };

        dfs(0, 0, 0);
        return static_cast<int>(answer);
    }
};


// -----------------------------------------------------------------------------
// 2. SUBSET DYNAMIC PROGRAMMING (BITMASK DP)
// -----------------------------------------------------------------------------
// State:
//   dp[mask] = minimum possible latest bloom day after planting exactly the
//              seeds represented by mask, with all those seeds planted.
//
// Observation:
//   The total planting time after completing a particular set is independent
//   of the order: it is sum(plantTime[i]) over set bits in mask.
//   However, the latest bloom time depends on the order, so dp stores the
//   minimum possible value of that maximum.
//
// Transition:
//   Let elapsed be the total planting time of mask. Append an unplanted seed i:
//       next = mask | (1 << i)
//       dp[next] = min(dp[next],
//                      max(dp[mask], elapsed + plantTime[i] + growTime[i]))
//
// Complexity:
//   Time:  O(n * 2^n)
//   Space: O(2^n)
//
// Practicality:
//   This is an exact dynamic-programming formulation, but it is only suitable
//   for small n. It cannot handle the stated maximum n = 100,000.

class SolutionBitmaskDP {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        const int n = static_cast<int>(plantTime.size());

        // A bitmask DP requires a small n. This guard prevents undefined shifts
        // or an accidental enormous allocation if used outside its intended
        // educational range. LeetCode's actual constraints need the greedy
        // implementation below.
        if (n >=  int(sizeof(unsigned int) * 8)) {
            return -1;
        }

        const unsigned int stateCount = 1u << n;
        const long long INF = LLONG_MAX / 4;

        vector<long long> dp(stateCount, INF);
        vector<long long> plantingSum(stateCount, 0);

        dp[0] = 0;

        for (unsigned int mask = 1; mask < stateCount; ++mask) {
            unsigned int bit = mask & (~mask + 1u);
            int i = __builtin_ctz(bit);
            plantingSum[mask] =
                plantingSum[mask ^ bit] + plantTime[i];
        }

        for (unsigned int mask = 0; mask < stateCount; ++mask) {
            if (dp[mask] == INF) continue;

            long long elapsed = plantingSum[mask];

            for (int i = 0; i < n; ++i) {
                if (mask & (1u << i)) continue;

                unsigned int nextMask = mask | (1u << i);
                long long bloomDay =
                    elapsed + plantTime[i] + growTime[i];

                dp[nextMask] = min(
                    dp[nextMask],
                    max(dp[mask], bloomDay)
                );
            }
        }

        return static_cast<int>(dp[stateCount - 1]);
    }
};


// -----------------------------------------------------------------------------
// 3. OPTIMAL GREEDY: SORT BY DESCENDING GROW TIME
// -----------------------------------------------------------------------------
// Intuition:
//   Seeds with longer growth periods should be planted earlier. Their growth
//   can then proceed in parallel while we plant the remaining seeds.
//
// Algorithm:
//   1. Create (growTime[i], plantTime[i]) pairs.
//   2. Sort by growTime in descending order.
//   3. Plant in that order, maintaining cumulative planting time.
//   4. For each seed, calculate cumulativePlantingTime + growTime[i].
//   5. The answer is the maximum bloom day.
//
// Why descending growTime is optimal (exchange argument):
//   Consider two adjacent seeds A and B, with planting durations pA, pB and
//   growth durations gA, gB. Suppose A is planted before B.
//
//   Their relevant bloom times in order A -> B are:
//       T + pA + gA
//       T + pA + pB + gB
//
//   In order B -> A they are:
//       T + pB + gB
//       T + pB + pA + gA
//
//   If gA < gB, placing B first cannot increase the maximum of these two
//   completion-plus-growth values. Therefore, any adjacent inversion where a
//   shorter-growth seed precedes a longer-growth seed can be swapped without
//   worsening the answer. Repeatedly removing such inversions yields a
//   non-increasing growTime order, which is optimal.
//
// Complexity:
//   Time:  O(n log n) — sorting dominates the O(n) scan.
//   Space: O(n)       — storing the pairs (excluding implementation-dependent
//                       sorting stack space).
//
// This is the recommended solution for the given constraints.

class SolutionGreedySort {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        const int n = static_cast<int>(plantTime.size());

        vector<pair<int, int>> seeds;
        seeds.reserve(n);

        for (int i = 0; i < n; ++i) {
            seeds.push_back({growTime[i], plantTime[i]});
        }

        sort(seeds.begin(), seeds.end(),
             [](const auto& a, const auto& b) {
                 return a.first > b.first;
             });

        long long currentDay = 0;
        long long answer = 0;

        for (const auto& [growth, planting] : seeds) {
            currentDay += planting;
            answer = max(answer, currentDay + growth);
        }

        return static_cast<int>(answer);
    }
};


// -----------------------------------------------------------------------------
// 4. GREEDY WITHOUT SORT(): REPEATEDLY SELECT THE LARGEST GROW TIME
// -----------------------------------------------------------------------------
// Intuition:
//   This produces exactly the same descending-growTime order as the optimal
//   greedy solution, but finds the next seed by scanning all remaining seeds.
//
// Complexity:
//   Time:  O(n^2) — up to n scans, each examining O(n) seeds.
//   Space: O(n)   — used[].
//
// Practicality:
//   This is a useful intermediate implementation to understand the greedy
//   ordering independently of a sorting library. It is too slow for n = 1e5.

class SolutionGreedySelection {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        const int n = static_cast<int>(plantTime.size());
        vector<bool> used(n, false);

        long long currentDay = 0;
        long long answer = 0;

        for (int step = 0; step < n; ++step) {
            int best = -1;

            for (int i = 0; i < n; ++i) {
                if (used[i]) continue;

                if (best == -1 || growTime[i] > growTime[best]) {
                    best = i;
                }
            }

            used[best] = true;
            currentDay += plantTime[best];
            answer = max(answer, currentDay + growTime[best]);
        }

        return static_cast<int>(answer);
    }
};


/*
    RECOMMENDED LEETCODE SUBMISSION:

    class Solution {
    public:
        int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
            vector<int> order(plantTime.size());
            iota(order.begin(), order.end(), 0);

            sort(order.begin(), order.end(), [&](int a, int b) {
                return growTime[a] > growTime[b];
            });

            long long day = 0, answer = 0;
            for (int i : order) {
                day += plantTime[i];
                answer = max(answer, day + growTime[i]);
            }
            return static_cast<int>(answer);
        }
    };

    Example 1:
      plantTime = [1,4,3], growTime = [2,3,1]
      Descending growth order: seed 1, seed 0, seed 2
      Planting completion days: 4, 5, 8
      Bloom days:               7, 7, 9
      Answer = 9

    Example 2:
      plantTime = [1,2,3,2], growTime = [2,1,2,1]
      One valid descending-growth order: seed 0, seed 2, seed 1, seed 3
      Planting completion days: 1, 4, 6, 8
      Bloom days:               3, 6, 7, 9
      Answer = 9

    Example 3:
      plantTime = [1], growTime = [1]
      Planting completion day = 1
      Bloom day = 1 + 1 = 2
      Answer = 2

    Important:
      - Growth happens in parallel with planting of other seeds.
      - Do not add all growth times together.
      - Sort by growTime descending, NOT by plantTime.
      - If two seeds have equal growTime, either order is optimal.
      - Use long long for cumulative planting time and bloom-day calculations.
*/
