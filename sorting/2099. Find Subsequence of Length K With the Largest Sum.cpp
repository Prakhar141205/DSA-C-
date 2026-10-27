#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 2099: Find Subsequence of Length K With the Largest Sum

Problem:
Select exactly k elements with the maximum possible sum, while preserving
their original relative order.

All approaches are included below. Call the desired method from main()
or copy that method into LeetCode's Solution class.

Let:
n = nums.size()
k = required subsequence length
U = 200001, the bounded value range [-100000, 100000]
*/


class Solution {
public:

    // ============================================================
    // APPROACH 1: BRUTE FORCE / BACKTRACKING
    // Time:  O(k * C(n, k))
    // Space: O(k) auxiliary, excluding the returned result
    //
    // Idea:
    // Try including or excluding each element. Evaluate every
    // subsequence of length k and retain the one with the largest sum.
    //
    // Usefulness:
    // Educational only; exponential time makes it impractical for
    // large inputs.
    // ============================================================

    vector<int> bestBrute;
    long long bestBruteSum;

    void bruteDfs(vector<int>& nums, int i, int k,
                  vector<int>& curr, long long sum) {
        if ((int)curr.size() == k) {
            if (sum > bestBruteSum) {
                bestBruteSum = sum;
                bestBrute = curr;
            }
            return;
        }

        if (i == (int)nums.size() ||
            (int)curr.size() + (int)nums.size() - i < k)
            return;

        // Choice 1: include nums[i].
        curr.push_back(nums[i]);
        bruteDfs(nums, i + 1, k, curr, sum + nums[i]);
        curr.pop_back();

        // Choice 2: exclude nums[i].
        bruteDfs(nums, i + 1, k, curr, sum);
    }

    vector<int> maxSubsequenceBruteForce(vector<int>& nums, int k) {
        bestBrute.clear();
        bestBruteSum = LLONG_MIN;

        vector<int> curr;
        bruteDfs(nums, 0, k, curr, 0);
        return bestBrute;
    }


    // ============================================================
    // APPROACH 2: SORTING + ORIGINAL INDICES (RECOMMENDED)
    // Time:  O(n log n + k log k) = O(n log n)
    // Space: O(n) for indexed pairs
    //
    // Idea:
    // Store {value, original_index}; sort by value descending;
    // keep k entries; sort those by original index to restore order.
    //
    // Usefulness:
    // Simple, reliable, and works for arbitrary integer values.
    // ============================================================

    vector<int> maxSubsequenceSorting(vector<int>& nums, int k) {
        vector<pair<int, int>> v;
        for (int i = 0; i < (int)nums.size(); i++)
            v.push_back({nums[i], i});

        sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        v.resize(k);

        sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        vector<int> ans;
        for (auto [val, idx] : v)
            ans.push_back(val);

        return ans;
    }


    // ============================================================
    // APPROACH 3: MIN-HEAP OF SIZE K
    // Time:  O(n log k + k log k)
    // Space: O(k) auxiliary
    //
    // Idea:
    // Keep the k largest {value, index} pairs in a min-heap.
    // If heap size exceeds k, remove its smallest pair.
    // Finally, sort selected pairs by original index.
    //
    // Usefulness:
    // Especially useful when k is much smaller than n.
    //
    // Tie note:
    // Pairs are ordered lexicographically, so equal values are
    // broken by index. Any maximum-sum answer is accepted.
    // ============================================================

    vector<int> maxSubsequenceHeap(vector<int>& nums, int k) {
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        for (int i = 0; i < (int)nums.size(); i++) {
            pq.push({nums[i], i});
            if ((int)pq.size() > k)
                pq.pop();
        }

        vector<pair<int, int>> selected;
        while (!pq.empty()) {
            selected.push_back(pq.top());
            pq.pop();
        }

        sort(selected.begin(), selected.end(),
             [](const auto& a, const auto& b) {
                 return a.second < b.second;
             });

        vector<int> ans;
        for (auto [val, idx] : selected)
            ans.push_back(val);

        return ans;
    }


    // ============================================================
    // APPROACH 4: NTH_ELEMENT + ORIGINAL INDICES
    // Average time: O(n + k log k)
    // Space: O(n) for indexed pairs
    //
    // Idea:
    // nth_element partitions the range so its first k entries
    // contain the k largest values under a descending comparator.
    // Their order is unspecified, so sort them by original index.
    //
    // Usefulness:
    // Efficient average-time top-k selection without full sorting.
    //
    // Important:
    // Skip nth_element when k == n because begin() + k == end().
    // The C++ standard does not guarantee linear worst-case time.
    // ============================================================

    vector<int> maxSubsequenceNthElement(vector<int>& nums, int k) {
        vector<pair<int, int>> v;
        for (int i = 0; i < (int)nums.size(); i++)
            v.push_back({nums[i], i});

        if (k < (int)v.size()) {
            nth_element(
                v.begin(), v.begin() + k, v.end(),
                [](const auto& a, const auto& b) {
                    return a.first > b.first;
                }
            );
        }

        v.resize(k);

        sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        vector<int> ans;
        for (auto [val, idx] : v)
            ans.push_back(val);

        return ans;
    }


    // ============================================================
    // APPROACH 5: PARTIAL_SORT + ORIGINAL INDICES
    // Time:  O(n log k + k log k)
    // Space: O(n) for indexed pairs
    //
    // Idea:
    // partial_sort sorts the first k entries by descending value.
    // Then sort those k entries by original index.
    //
    // Usefulness:
    // Use when you want the top k elements sorted by value.
    // ============================================================

    vector<int> maxSubsequencePartialSort(vector<int>& nums, int k) {
        vector<pair<int, int>> v;
        for (int i = 0; i < (int)nums.size(); i++)
            v.push_back({nums[i], i});

        partial_sort(
            v.begin(), v.begin() + k, v.end(),
            [](const auto& a, const auto& b) {
                return a.first > b.first;
            }
        );

        v.resize(k);

        sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        vector<int> ans;
        for (auto [val, idx] : v)
            ans.push_back(val);

        return ans;
    }


    // ============================================================
    // APPROACH 6: COUNTING / VALUE BUCKETS
    // Value range: [-100000, 100000], U = 200001
    // Time:  O(n + U + k log k)
    // Space: O(n + U)
    //
    // Idea:
    // Bucket original indices by value. Traverse values from largest
    // to smallest, take k indices, then sort indices to restore order.
    //
    // Usefulness:
    // Useful when values are bounded integers.
    // More memory-intensive than a heap when k is small.
    // ============================================================

    vector<int> maxSubsequenceBuckets(vector<int>& nums, int k) {
        const int OFFSET = 100000;
        const int U = 200001;

        vector<vector<int>> bucket(U);

        for (int i = 0; i < (int)nums.size(); i++)
            bucket[nums[i] + OFFSET].push_back(i);

        vector<int> indices;
        indices.reserve(k);

        for (int x = U - 1; x >= 0 && (int)indices.size() < k; x--) {
            for (int idx : bucket[x]) {
                indices.push_back(idx);
                if ((int)indices.size() == k)
                    break;
            }
        }

        sort(indices.begin(), indices.end());

        vector<int> ans;
        for (int idx : indices)
            ans.push_back(nums[idx]);

        return ans;
    }


    // ============================================================
    // APPROACH 7: DYNAMIC PROGRAMMING
    // Time:  O(n * k)
    // Space: O(n * k)
    //
    // State:
    // dp[i][j] = maximum sum using exactly j elements from first i.
    //
    // Transition:
    // Skip nums[i-1], or take nums[i-1].
    //
    // Usefulness:
    // Correct but unnecessary for this problem; useful when additional
    // constraints make simple top-k selection insufficient.
    // ============================================================

    vector<int> maxSubsequenceDP(vector<int>& nums, int k) {
        int n = nums.size();
        const long long NEG = LLONG_MIN / 4;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, NEG)
        );

        for (int i = 0; i <= n; i++)
            dp[i][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= min(i, k); j++) {
                // Option 1: skip current element.
                dp[i][j] = dp[i - 1][j];

                // Option 2: take current element, if previous state is valid.
                if (dp[i - 1][j - 1] != NEG) {
                    dp[i][j] = max(
                        dp[i][j],
                        dp[i - 1][j - 1] + nums[i - 1]
                    );
                }
            }
        }

        vector<int> ans;
        int i = n, j = k;

        // Backtrack to recover one optimal subsequence.
        while (j > 0) {
            if (i > 0 && dp[i][j] == dp[i - 1][j]) {
                // Skipping is also optimal; either choice is valid.
                i--;
            } else {
                ans.push_back(nums[i - 1]);
                i--;
                j--;
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }


    // ============================================================
    // APPROACH 8: REPEATED MAXIMUM SEARCH
    // Time:  O(n * k + k log k)
    // Space: O(n)
    //
    // Idea:
    // Repeatedly scan for the largest unselected value, save its index,
    // and finally sort selected indices to restore original order.
    //
    // Usefulness:
    // Easy to understand, but inefficient when k is large.
    // ============================================================

    vector<int> maxSubsequenceRepeatedMax(vector<int>& nums, int k) {
        int n = nums.size();
        vector<bool> used(n, false);
        vector<int> indices;

        for (int t = 0; t < k; t++) {
            int best = -1;

            for (int i = 0; i < n; i++) {
                if (used[i])
                    continue;

                // Strict > keeps the earlier index on equal values.
                if (best == -1 || nums[i] > nums[best])
                    best = i;
            }

            used[best] = true;
            indices.push_back(best);
        }

        sort(indices.begin(), indices.end());

        vector<int> ans;
        for (int idx : indices)
            ans.push_back(nums[idx]);

        return ans;
    }


    // LeetCode's required method.
    // Recommended default: sorting + original indices.
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        return maxSubsequenceSorting(nums, k);
    }
};


/*
SUMMARY

1. Sorting + indices:
   O(n log n) time, O(n) space.
   Best simple general-purpose solution.

2. Min-heap of size k:
   O(n log k + k log k) time, O(k) space.
   Useful when k is small.

3. nth_element:
   Average O(n + k log k) time, O(n) space.
   Good for selection without fully sorting.

4. partial_sort:
   O(n log k + k log k) time, O(n) space.
   Useful when the top k elements must be sorted by value.

5. Buckets:
   O(n + U + k log k) time, O(n + U) space.
   Useful for bounded integer values.

6. DP:
   O(nk) time and space.
   Correct, but unnecessary here.

7. Brute force and repeated maximum search:
   Primarily educational; inefficient for larger inputs.

Core insight:
Select the k largest values, remember their original indices, and
restore ascending index order to obtain a valid subsequence.
*/
