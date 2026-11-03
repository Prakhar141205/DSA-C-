class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        int n = arr.size();

        unordered_map<int, long long> mp;
        sort(begin(arr), end(arr));
        mp[arr[0]] = 1;
        for(int i=1; i<n; i++) {
            int root = arr[i];
            mp[root] = 1;


            for(int j=0; j<i; j++) {
                int leftChild = arr[j];

                if(root%leftChild == 0 and (mp.find(arr[i]/leftChild) != mp.end())) {

                    mp[root] += (mp[leftChild] * mp[arr[i]/leftChild]);
                }
            }
        }
        long long result = 0;
        const int mod = 1e9+7;
        for(auto it : mp ) {
            result = (result + it.second) % mod;
        }
        return result;
    } 
};

#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 823 - Binary Trees With Factors

    A non-leaf node x can have children a and b if:
        a * b == x
    Both children must be values present in arr. A value can be reused
    any number of times, and left/right child order matters.

    DP definition:
        dp[x] = number of valid binary trees with root value x.

    Base case:
        Every value can form a single-node tree, so dp[x] starts at 1.

    Transition:
        For every factor pair a * b = x:
            dp[x] += dp[a] * dp[b]

    Since arr contains unique values, sort it and process in increasing
    order so every factor's DP value is already computed.

    All classes below are independent. Rename the chosen class to Solution
    before submitting to LeetCode.
*/

static constexpr long long MOD = 1'000'000'007LL;


// -----------------------------------------------------------------------------
// Approach 1: Brute force factor-pair enumeration + linear searches
// Data structures: sorted vector + DP vector.
// Time: O(n^3) worst case; Space: O(n).
// For every root x, try every ordered pair (a,b), then linearly search whether
// both factors exist in arr. Educational baseline; can be too slow.
// -----------------------------------------------------------------------------
class SolutionBruteForce {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int n = (int)arr.size();
        vector<long long> dp(n, 1);
        long long answer = 0;

        for (int i = 0; i < n; ++i) {
            long long root = arr[i];

            for (int j = 0; j < i; ++j) {
                for (int k = 0; k < i; ++k) {
                    if (1LL * arr[j] * arr[k] != root) continue;

                    // Each ordered pair is considered separately.
                    dp[i] = (dp[i] + dp[j] * dp[k]) % MOD;
                }
            }

            answer = (answer + dp[i]) % MOD;
        }

        return (int)answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Sorting + unordered_map DP
// Data structures: sorted vector + unordered_map<value, ways>.
// Average Time: O(n^2); Space: O(n).
//
// For each x, scan possible left factors a < x. If a divides x and b=x/a
// exists among already processed values, add dp[a]*dp[b].
// Each factor pair is considered once by scanning a from the beginning.
// -----------------------------------------------------------------------------
class SolutionHashMapDP {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        unordered_map<long long, long long> dp;
        dp.reserve(arr.size() * 2);

        long long answer = 0;

        for (long long root : arr) {
            long long ways = 1; // Single-node tree.

            for (long long left : arr) {
                if (left >= root) break;
                if (root % left != 0) continue;

                long long right = root / left;
                auto it = dp.find(right);

                if (it != dp.end()) {
                    // dp[left] exists because left < root and was processed.
                    ways = (ways + dp[left] * it->second) % MOD;
                }
            }

            dp[root] = ways;
            answer = (answer + ways) % MOD;
        }

        return (int)answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Sorting + unordered_set membership + DP vector
// Data structures: sorted vector + unordered_set + vector DP.
// Average Time: O(n^2); Space: O(n).
//
// The set answers whether the complementary factor exists. Its DP value is
// retrieved using the index map.
// -----------------------------------------------------------------------------
class SolutionHashSetDP {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int n = (int)arr.size();
        unordered_set<long long> present(arr.begin(), arr.end());
        unordered_map<long long, int> index;
        index.reserve(n * 2);

        for (int i = 0; i < n; ++i) {
            index[arr[i]] = i;
        }

        vector<long long> dp(n, 1);
        long long answer = 0;

        for (int i = 0; i < n; ++i) {
            long long root = arr[i];

            for (int j = 0; j < i; ++j) {
                long long left = arr[j];

                if (root % left != 0) continue;

                long long right = root / left;
                if (!present.count(right)) continue;

                int k = index[right];
                if (k >= i) continue;

                dp[i] = (dp[i] + dp[j] * dp[k]) % MOD;
            }

            answer = (answer + dp[i]) % MOD;
        }

        return (int)answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 4: Sorting + binary search + DP vector
// Data structures: sorted vector + vector DP.
// Time: O(n^2 log n); Space: O(n).
// For each root and possible left factor, binary-search the complementary
// factor. This avoids hash tables and gives deterministic lookup complexity.
// -----------------------------------------------------------------------------
class SolutionBinarySearchDP {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int n = (int)arr.size();
        vector<long long> dp(n, 1);
        long long answer = 0;

        for (int i = 0; i < n; ++i) {
            long long root = arr[i];

            for (int j = 0; j < i; ++j) {
                long long left = arr[j];

                if (root % left != 0) continue;

                long long right = root / left;
                auto it = lower_bound(arr.begin(), arr.begin() + i, right);

                if (it == arr.begin() + i || *it != right) continue;

                int k = (int)(it - arr.begin());
                dp[i] = (dp[i] + dp[j] * dp[k]) % MOD;
            }

            answer = (answer + dp[i]) % MOD;
        }

        return (int)answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Sorting + two-pointer factor-pair enumeration
// Data structures: sorted vector + DP vector.
// Time: O(n^2); Space: O(n).
//
// For each root, use two pointers over earlier values to find factor pairs.
// When arr[left] * arr[right] == root, add dp[left]*dp[right].
// If left != right, also add the swapped-child ordering.
// This avoids hash lookups and avoids scanning impossible pairs.
// -----------------------------------------------------------------------------
class SolutionTwoPointersDP {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        int n = (int)arr.size();
        vector<long long> dp(n, 1);
        long long answer = 0;

        for (int i = 0; i < n; ++i) {
            long long root = arr[i];
            int left = 0;
            int right = i - 1;

            while (left <= right) {
                long long product = 1LL * arr[left] * arr[right];

                if (product < root) {
                    ++left;
                } else if (product > root) {
                    --right;
                } else {
                    long long contribution = dp[left] * dp[right] % MOD;
                    dp[i] = (dp[i] + contribution) % MOD;

                    if (left != right) {
                        dp[i] = (dp[i] + contribution) % MOD;
                    }

                    ++left;
                    --right;
                }
            }

            answer = (answer + dp[i]) % MOD;
        }

        return (int)answer;
    }
};


/*
    Example 1:
      arr = [2,4]

      dp[2] = 1
        Only tree: [2]

      dp[4] = 1
        Single-node tree [4]
      Factor pair:
        2 * 2 = 4
        Add dp[2] * dp[2] = 1

      dp[4] = 2

      Total = dp[2] + dp[4] = 1 + 2 = 3.


    Example 2:
      arr = [2,4,5,10]

      dp[2] = 1
      dp[4] = 1 + dp[2]*dp[2] = 2
      dp[5] = 1
      dp[10] = 1 + dp[2]*dp[5] + dp[5]*dp[2] = 3

      Total = 1 + 2 + 1 + 3 = 7.


    Important implementation details:
      - Use 1LL * a * b to avoid 32-bit multiplication overflow.
      - Use long long for DP multiplication before taking modulo.
      - Left/right child order matters. For distinct factors a and b,
        (a,b) and (b,a) are different ordered binary trees.
      - For equal factors a == b, count the combination only once.
      - Sorting ensures child values are smaller than the root and their
        DP values are already available.

    Recommended:
      - Approach 2: standard hash-map DP, concise and efficient.
      - Approach 5: useful to revise two-pointer factor-pair enumeration.
*/
