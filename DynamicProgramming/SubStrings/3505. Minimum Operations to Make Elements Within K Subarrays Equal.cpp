/*
    LeetCode 3505. Minimum Operations to Make Elements Within K Subarrays Equal
    Language: C++17

    We need to choose at least k pairwise non-overlapping windows, each of
    length exactly x. Every chosen window is made constant at minimum cost.

    Key observation:
        The minimum cost to make one window equal is the sum of absolute
        differences from its median.

    For a sorted window a[0..x-1], choose a median m:
        cost = sum(|a[i] - m|)

    Since we need at least k windows and all costs are non-negative, an
    optimal solution can be represented by choosing exactly k windows.

    Each approach is a separate class. Rename the chosen class to Solution.
*/

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <set>
#include <vector>
using namespace std;

// -----------------------------------------------------------------------------
// Shared DP idea used by the optimized approaches
//
// Let cost[s] be the minimum cost to make nums[s .. s+x-1] equal.
//
// dp[j][i] = minimum cost to select j non-overlapping windows using only
//            the first i elements.
//
// Transition:
//   1. Skip element i-1: dp[j][i-1]
//   2. Take the window [i-x, i): dp[j-1][i-x] + cost[i-x]
//
// Therefore:
//   dp[j][i] = min(dp[j][i-1], dp[j-1][i-x] + cost[i-x])
//
// We only need the previous j-row, so rolling DP uses O(n) memory.
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Approach 1: Two multisets (lower half + upper half) + rolling DP
// Technique: Sliding window median using two balanced multisets
//
// Time:  O(n log x + n*k)
// Space: O(n)
//
// low contains the smallest ceil(x/2) elements.
// high contains the remaining elements.
// The median is the largest element in low.
//
// lowSum and highSum let us calculate the sum of absolute differences in O(1)
// once the two multisets are balanced.
// -----------------------------------------------------------------------------
class Solution_TwoMultisets {
private:
    multiset<int> low, high;
    long long lowSum = 0, highSum = 0;
    int targetLowSize;

    void moveLowToHigh() {
        auto it = prev(low.end());
        int value = *it;
        low.erase(it);
        lowSum -= value;
        high.insert(value);
        highSum += value;
    }

    void moveHighToLow() {
        auto it = high.begin();
        int value = *it;
        high.erase(it);
        highSum -= value;
        low.insert(value);
        lowSum += value;
    }

    void rebalance() {
        while (static_cast<int>(low.size()) > targetLowSize)
            moveLowToHigh();

        while (static_cast<int>(low.size()) < targetLowSize)
            moveHighToLow();
    }

    void add(int value) {
        if (low.empty() || value <= *prev(low.end())) {
            low.insert(value);
            lowSum += value;
        } else {
            high.insert(value);
            highSum += value;
        }
        rebalance();
    }

    void remove(int value) {
        auto itLow = low.find(value);
        if (itLow != low.end()) {
            low.erase(itLow);
            lowSum -= value;
        } else {
            auto itHigh = high.find(value);
            high.erase(itHigh);
            highSum -= value;
        }
        rebalance();
    }

    long long currentCost() const {
        long long median = *prev(low.end());

        long long leftCost =
            median * static_cast<long long>(low.size()) - lowSum;

        long long rightCost =
            highSum - median * static_cast<long long>(high.size());

        return leftCost + rightCost;
    }

    vector<long long> calculateWindowCosts(const vector<int>& nums, int x) {
        int n = static_cast<int>(nums.size());
        targetLowSize = (x + 1) / 2;

        low.clear();
        high.clear();
        lowSum = highSum = 0;

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; ++i)
            add(nums[i]);

        cost[0] = currentCost();

        for (int start = 1; start + x <= n; ++start) {
            remove(nums[start - 1]);
            add(nums[start + x - 1]);
            cost[start] = currentCost();
        }

        return cost;
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = static_cast<int>(nums.size());
        vector<long long> cost = calculateWindowCosts(nums, x);

        const long long INF = LLONG_MAX / 4;
        vector<long long> previous(n + 1, 0), current(n + 1, INF);

        // previous[i] is the minimum cost for selecting 0 windows:
        // it is 0 for every prefix length.
        for (int chosen = 1; chosen <= k; ++chosen) {
            fill(current.begin(), current.end(), INF);

            for (int i = 1; i <= n; ++i) {
                // Option 1: do not use a window ending at i.
                current[i] = current[i - 1];

                // Option 2: choose the window [i-x, i).
                if (i >= x && previous[i - x] != INF) {
                    long long take =
                        previous[i - x] + cost[i - x];
                    current[i] = min(current[i], take);
                }
            }

            previous.swap(current);
        }

        return previous[n];
    }
};

// -----------------------------------------------------------------------------
// Approach 2: Coordinate compression + Fenwick trees + rolling DP
// Technique: Fenwick tree for counts and Fenwick tree for value sums
//
// Time:  O(n log n + n log n + n*k)
// Space: O(n)
//
// Two Fenwick trees represent the current window:
//   countBIT: frequency of each compressed value
//   sumBIT:   sum of values at each compressed coordinate
//
// Find the lower median by a Fenwick order-statistic query. Prefix counts and
// sums then give the absolute-difference cost in O(log n) per window.
// This avoids multiset node allocations and is useful when learning BITs.
// -----------------------------------------------------------------------------
class Solution_Fenwick {
private:
    class Fenwick {
        int n;
        vector<long long> bit;

    public:
        explicit Fenwick(int size = 0) : n(size), bit(size + 1, 0) {}

        void add(int index, long long delta) {
            for (; index <= n; index += index & -index)
                bit[index] += delta;
        }

        long long query(int index) const {
            long long result = 0;
            for (; index > 0; index -= index & -index)
                result += bit[index];
            return result;
        }

        // Return the smallest 1-based index whose prefix sum >= target.
        int kth(long long target) const {
            int index = 0;
            int step = 1;
            while ((step << 1) <= n)
                step <<= 1;

            for (; step > 0; step >>= 1) {
                int next = index + step;
                if (next <= n && bit[next] < target) {
                    index = next;
                    target -= bit[next];
                }
            }
            return index + 1;
        }
    };

    vector<long long> calculateWindowCosts(
        const vector<int>& nums,
        int x,
        const vector<int>& values
    ) {
        int n = static_cast<int>(nums.size());
        int m = static_cast<int>(values.size());

        Fenwick countBIT(m), sumBIT(m);
        long long windowSum = 0;

        auto compressedIndex = [&](int value) {
            return static_cast<int>(
                lower_bound(values.begin(), values.end(), value) -
                values.begin()
            ) + 1;
        };

        auto addValue = [&](int value, int delta) {
            int index = compressedIndex(value);
            countBIT.add(index, delta);
            sumBIT.add(index, 1LL * delta * value);
            windowSum += 1LL * delta * value;
        };

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; ++i)
            addValue(nums[i], 1);

        for (int start = 0; start + x <= n; ++start) {
            int medianIndex = countBIT.kth((x + 1) / 2);
            long long median = values[medianIndex - 1];

            long long countLE = countBIT.query(medianIndex);
            long long sumLE = sumBIT.query(medianIndex);

            long long leftCost = median * countLE - sumLE;
            long long rightCount = x - countLE;
            long long rightSum = windowSum - sumLE;
            long long rightCost = rightSum - median * rightCount;

            cost[start] = leftCost + rightCost;

            if (start + x < n) {
                addValue(nums[start], -1);
                addValue(nums[start + x], 1);
            }
        }

        return cost;
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = static_cast<int>(nums.size());

        vector<int> values = nums;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        vector<long long> cost = calculateWindowCosts(nums, x, values);

        const long long INF = LLONG_MAX / 4;
        vector<long long> previous(n + 1, 0), current(n + 1, INF);

        for (int chosen = 1; chosen <= k; ++chosen) {
            fill(current.begin(), current.end(), INF);

            for (int i = 1; i <= n; ++i) {
                current[i] = current[i - 1];

                if (i >= x && previous[i - x] != INF) {
                    current[i] = min(
                        current[i],
                        previous[i - x] + cost[i - x]
                    );
                }
            }

            previous.swap(current);
        }

        return previous[n];
    }
};

// -----------------------------------------------------------------------------
// Approach 3: Sort every window independently + rolling DP
// Technique: Sorting + median + dynamic programming
//
// Time:  O((n-x+1) * x log x + n*k)
// Space: O(n + x)
//
// This is a straightforward reference implementation, but it is too slow for
// n = 100,000 in the worst case. It is useful for understanding the reduction
// to window costs and for checking optimized implementations on small tests.
// -----------------------------------------------------------------------------
class Solution_BruteWindowSorting {
private:
    long long getCost(const vector<int>& nums, int start, int x) {
        vector<int> window;
        window.reserve(x);

        for (int i = start; i < start + x; ++i)
            window.push_back(nums[i]);

        sort(window.begin(), window.end());

        long long median = window[(x - 1) / 2];
        long long cost = 0;

        for (int value : window)
            cost += llabs(1LL * value - median);

        return cost;
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = static_cast<int>(nums.size());
        vector<long long> cost(n - x + 1);

        for (int start = 0; start + x <= n; ++start)
            cost[start] = getCost(nums, start, x);

        const long long INF = LLONG_MAX / 4;
        vector<long long> previous(n + 1, 0), current(n + 1, INF);

        for (int chosen = 1; chosen <= k; ++chosen) {
            fill(current.begin(), current.end(), INF);

            for (int i = 1; i <= n; ++i) {
                current[i] = current[i - 1];

                if (i >= x && previous[i - x] != INF) {
                    current[i] = min(
                        current[i],
                        previous[i - x] + cost[i - x]
                    );
                }
            }

            previous.swap(current);
        }

        return previous[n];
    }
};

/*
    DRY RUN — Example 1

    nums = [5, -2, 1, 3, 7, 3, 6, 4, -1]
    x = 3, k = 2

    First calculate the cost of making each length-3 window equal.
    The best value to make all elements equal is a median.

    Window [5, -2, 1]:
        Sorted: [-2, 1, 5]
        Median = 1
        Cost = |5-1| + |-2-1| + |1-1| = 7

    Window [-2, 1, 3]:
        Sorted: [-2, 1, 3]
        Median = 1
        Cost = 5

    Window [1, 3, 7]:
        Sorted: [1, 3, 7]
        Median = 3
        Cost = 6

    Window [3, 7, 3]:
        Sorted: [3, 3, 7]
        Median = 3
        Cost = 4

    Window [7, 3, 6]:
        Sorted: [3, 6, 7]
        Median = 6
        Cost = 4

    Window [3, 6, 4]:
        Sorted: [3, 4, 6]
        Median = 4
        Cost = 3

    Window [6, 4, -1]:
        Sorted: [-1, 4, 6]
        Median = 4
        Cost = 7

    Window costs by starting index:
        start:  0  1  2  3  4  5  6
        cost:   7  5  6  4  4  3  7

    We need two windows that do not overlap.
    Choose start 1: indices [1, 2, 3] = [-2, 1, 3], cost 5.
    Choose start 5: indices [5, 6, 7] = [3, 6, 4], cost 3.
    These windows do not overlap.

    Total = 5 + 3 = 8, matching the sample output.

    DP STATE:
        previous[i] = minimum cost to choose chosen-1 windows in first i items.
        current[i]  = minimum cost to choose chosen windows in first i items.

    At each prefix i:
        Skip: current[i-1]
        Take: previous[i-x] + cost[i-x]

    WHY THE DP ENFORCES NON-OVERLAP:
        When taking a window [i-x, i), we append it only to a solution using
        the first i-x elements. Earlier selected windows therefore finish no
        later than i-x, so they cannot overlap the new window.

    COMPLEXITIES:
        Approach 1: O(n log x + n*k) time, O(n) auxiliary space.
        Approach 2: O(n log n + n log n + n*k) time, O(n) auxiliary space.
        Approach 3: O((n-x+1)*x log x + n*k) time, O(n+x) space.

    RECOMMENDATION:
        Use Approach 1 for a clean optimized solution.
        Use Approach 2 to practice Fenwick trees and order statistics.
*/
