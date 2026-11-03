#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 1512 - Number of Good Pairs

    A pair (i, j) is good when:
        nums[i] == nums[j] AND i < j

    Revision focus:
      This problem can be solved using several data structures:
        1. Nested loops (no extra data structure)
        2. Sorting + vector
        3. Unordered map (frequency counting)
        4. Ordered map (frequency counting)
        5. Fixed-size frequency array (uses nums[i] <= 100)
        6. Vector of index groups

    These are meaningfully different approaches, not artificial variations.
    Each class is independent. Rename the chosen class to Solution before
    submitting it to LeetCode.
*/


// -----------------------------------------------------------------------------
// Approach 1: Brute force - check every pair of indices
// Data structure: None beyond the input vector.
// Time: O(n^2); Space: O(1).
//
// For each i, inspect only j > i. This directly enforces i < j.
// -----------------------------------------------------------------------------
class SolutionBruteForce {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int n = (int)nums.size();
        int answer = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] == nums[j]) {
                    ++answer;
                }
            }
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Sorting + count equal-value groups
// Data structure: Vector.
// Time: O(n log n); Space: O(1) auxiliary if sorting in place
// (sorting implementation may use O(log n) stack space).
//
// Equal values become consecutive. A group of size k contributes
// k*(k-1)/2 pairs.
// -----------------------------------------------------------------------------
class SolutionSorting {
public:
    int numIdenticalPairs(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int answer = 0;
        int n = (int)nums.size();

        for (int i = 0; i < n;) {
            int j = i;

            while (j < n && nums[j] == nums[i]) {
                ++j;
            }

            int frequency = j - i;
            answer += frequency * (frequency - 1) / 2;
            i = j;
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Unordered map - count previous occurrences
// Data structure: unordered_map.
// Average Time: O(n); worst-case hash behavior can be worse.
// Space: O(k), k = number of distinct values.
//
// At index i, if this value has appeared f times before, it forms f new
// good pairs with those earlier indices. Add f, then increment its count.
// -----------------------------------------------------------------------------
class SolutionUnorderedMap {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int, int> frequency;
        frequency.reserve(nums.size());

        int answer = 0;

        for (int x : nums) {
            answer += frequency[x];
            ++frequency[x];
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 4: Ordered map - count previous occurrences
// Data structure: map (balanced search tree).
// Time: O(n log k); Space: O(k).
//
// Same counting invariant as Approach 3, but map keeps keys ordered.
// Ordering is not needed for this problem; this is included to revise the
// ordered-map frequency-counting pattern.
// -----------------------------------------------------------------------------
class SolutionOrderedMap {
public:
    int numIdenticalPairs(vector<int>& nums) {
        map<int, int> frequency;
        int answer = 0;

        for (int x : nums) {
            answer += frequency[x];
            ++frequency[x];
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Fixed-size frequency array
// Data structure: Array.
// Time: O(n + U); Space: O(U), U = 101.
// Uses the constraint 1 <= nums[i] <= 100.
//
// `frequency[x]` counts how many x values have already been processed.
// -----------------------------------------------------------------------------
class SolutionFrequencyArray {
public:
    int numIdenticalPairs(vector<int>& nums) {
        int frequency[101] = {};
        int answer = 0;

        for (int x : nums) {
            answer += frequency[x];
            ++frequency[x];
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 6: Vector of index groups
// Data structure: vector<vector<int>>.
// Time: O(n + U + sum(f_x^2)) with pair counting inside each group;
// worst-case O(n^2). Space: O(n + U).
//
// Group indices by value. Every group containing k indices contributes
// k choose 2 pairs. This approach explicitly stores the index groups and
// is useful for understanding the relationship between values and indices.
// -----------------------------------------------------------------------------
class SolutionIndexGroups {
public:
    int numIdenticalPairs(vector<int>& nums) {
        vector<vector<int>> positions(101);

        for (int i = 0; i < (int)nums.size(); ++i) {
            positions[nums[i]].push_back(i);
        }

        int answer = 0;

        for (const auto& indices : positions) {
            int k = (int)indices.size();

            // All indices in this group are distinct, and every pair is good
            // when the smaller index is chosen first.
            answer += k * (k - 1) / 2;
        }

        return answer;
    }
};


/*
    Dry run:
      nums = [1, 2, 3, 1, 1, 3]

      Process from left to right using a frequency table:

      x = 1: previous count = 0; answer = 0; freq[1] = 1
      x = 2: previous count = 0; answer = 0; freq[2] = 1
      x = 3: previous count = 0; answer = 0; freq[3] = 1
      x = 1: previous count = 1; answer = 1; freq[1] = 2
      x = 1: previous count = 2; answer = 3; freq[1] = 3
      x = 3: previous count = 1; answer = 4; freq[3] = 2

      Return 4.

    Combinatorial formula:
      If a value occurs k times, it contributes:
          C(k, 2) = k * (k - 1) / 2

      If distinct values have frequencies f1, f2, ..., fr:
          answer = sum(C(fi, 2)).

    Recommended:
      - Approach 5 (frequency array): best for the exact constraints,
        O(n) time and O(101) space.
      - Approach 3 (unordered_map): best general-purpose frequency pattern
        when the value range is not small or fixed.
      - Approach 1: simplest way to understand the definition.
*/
