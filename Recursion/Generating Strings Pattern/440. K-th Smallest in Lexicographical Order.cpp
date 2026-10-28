/*
    LeetCode 440 — K-th Smallest in Lexicographical Order
    ======================================================
    Given 1 <= k <= n <= 1e9, return the k-th integer in lexicographical order.

    Main idea:
      Treat numbers as nodes in a decimal prefix trie.
      For a prefix curr, count how many values <= n lie in its subtree.
      If that subtree contains fewer than or equal to the remaining positions,
      skip the entire subtree. Otherwise, descend into it.

    Approaches included:
      1. Brute force: convert 1..n to strings and sort
      2. Sort integers with a lexicographical comparator
      3. Generate the lexicographical traversal (DFS/trie)
      4. Optimized prefix-counting / trie navigation (recommended)
*/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------------------------------------
// Approach 1: Brute force — convert every number to a string, then sort.
// Time: O(n log n * D) approximately, D = number of digits.
// Space: O(n * D).
// Only feasible for small n.
// --------------------------------------------------------------------------
class SolutionBruteForce {
public:
    int findKthNumber(int n, int k) {
        vector<string> nums;
        nums.reserve(n);

        for (int x = 1; x <= n; ++x) {
            nums.push_back(to_string(x));
        }

        sort(nums.begin(), nums.end());

        return stoi(nums[k - 1]);
    }
};

// --------------------------------------------------------------------------
// Approach 2: Sort integers using lexicographical string comparison.
// Same basic complexity as Approach 1; avoids storing strings but converts
// during comparisons, which can make it slower.
// Time: O(n log n * D), space O(n) plus temporary string conversions.
// --------------------------------------------------------------------------
class SolutionLexicographicalSort {
public:
    int findKthNumber(int n, int k) {
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);

        sort(nums.begin(), nums.end(), [](int a, int b) {
            return to_string(a) < to_string(b);
        });

        return nums[k - 1];
    }
};

// --------------------------------------------------------------------------
// Approach 3: Generate numbers in lexicographical order using trie-style DFS.
//
// The children of prefix p are p*10 + digit, in digit order 0..9.
// A node itself comes before its descendants, which gives lexicographical
// ordering. Stop when the k-th number has been generated.
//
// Time: O(k) visited values (up to O(n)); space O(D) recursion depth,
// where D <= 10 for n <= 1e9.
// --------------------------------------------------------------------------
class SolutionTrieDFS {
private:
    int n;
    int target;
    int visited;
    int answer;

    bool dfs(long long current) {
        if (current > n) return false;

        ++visited;
        if (visited == target) {
            answer = (int)current;
            return true;
        }

        for (int digit = 0; digit <= 9; ++digit) {
            long long child = current * 10 + digit;
            if (child > n) break;
            if (dfs(child)) return true;
        }
        return false;
    }

public:
    int findKthNumber(int n_, int k) {
        n = n_;
        target = k;
        visited = 0;
        answer = -1;

        for (int first = 1; first <= 9; ++first) {
            if (dfs(first)) return answer;
        }
        return answer;
    }
};

// --------------------------------------------------------------------------
// Approach 4: Optimized prefix counting / trie navigation (recommended).
//
// countSteps(n, prefix, prefix+1) counts all numbers <= n whose decimal
// representation begins with prefix.
//
// At each step:
//   - If the current prefix subtree has <= k remaining positions, skip it.
//   - Otherwise, the answer lies below this prefix; descend one level.
//
// Time: O(D^2) in the standard implementation, D = number of digits;
//       at most about 10 levels for n <= 1e9.
// Space: O(1).
// --------------------------------------------------------------------------
class Solution {
private:
    long long countSteps(long long n, long long prefix, long long nextPrefix) {
        long long steps = 0;

        while (prefix <= n) {
            steps += min(n + 1, nextPrefix) - prefix;
            prefix *= 10;
            nextPrefix *= 10;
        }

        return steps;
    }

public:
    int findKthNumber(int n, int k) {
        long long current = 1;
        --k; // current = first lexicographical number

        while (k > 0) {
            long long steps = countSteps(n, current, current + 1);

            if (steps <= k) {
                // Skip this entire prefix subtree and move to its next sibling.
                current++;
                k -= (int)steps;
            } else {
                // The answer is inside this prefix subtree; go to first child.
                current *= 10;
                --k; // moving to the child itself consumes one position
            }
        }

        return (int)current;
    }
};

/*
    Complexity comparison
    -------------------------------------------------------------------------
    Approach                              Time                  Space
    -------------------------------------------------------------------------
    1. String conversion + sort           O(n log n * D)        O(n*D)
    2. Lexicographical comparator sort    O(n log n * D)        O(n)
    3. Trie-style DFS generation          O(k) worst O(n)       O(D)
    4. Prefix counting (recommended)      O(D^2)                 O(1)

    D = number of decimal digits in n (D <= 10 under the constraints).

    Example: n = 13, k = 2
      Lexicographical order starts: 1, 10, 11, 12, 13, 2, ...
      The answer is 10.

    Key insight:
      Do not generate every number for n up to 1e9. Count the size of each
      prefix subtree and skip entire subtrees until the k-th position is found.
*/


/************************************************************ C++ ************************************************/
//Approach-1 (Simple Recursion - DFS) - MEMORY LIMIT EXCEEDE (MLE)
//T.C : O(n)
//S.C : O(d) of system stack and O(n) for storing numbers in result array
class Solution {
public:
    void solve(int curr, int n, vector<int>& result) {
        if(curr > n)
            return;
        
        result.push_back(curr);

        for(int nextDigit = 0; nextDigit <= 9; nextDigit++) {
            int nextnum = curr*10 + nextDigit;
            
            if(nextnum > n)
                return;
            
            solve(nextnum, n, result);
        }
    }

    int findKthNumber(int n, int k) {
        vector<int> result;
        
        for(int num = 1; num <= 9; num++)
            solve(num, n, result);
        
        return result[k-1];
    }
};



//Approach-2 (Simple Recursion - DFS without storing in result) - TIME LIMIT EXCEEDE (TLE)
//T.C : O(n)
//S.C : O(d) of system stack
class Solution {
public:
    int count = 0;
    int result = 0;

    bool solve(long long curr, int n, int k) {
        if (curr > n)
            return false;
        
        count++;
        
        if (count == k) {
            result = curr;
            return true;
        }
        
        for (int nextDigit = 0; nextDigit <= 9; nextDigit++) {
            long long nextnum = curr * 10 + nextDigit;
            if (nextnum > n)
                break;
            
            if (solve(nextnum, n, k)) {
                return true;
            }
        }
        
        return false;
    }

    int findKthNumber(int n, int k) {
        for (long long num = 1; num <= 9; num++) {
            if (solve(num, n, k)) {
                break;
            }
        }
        
        return result;
    }
};



//Approach-3 (Optimal) - ACCEPTED
//T.C : O((logn)^2)
//S.C : O(log(n)) system resursion stack
class Solution {
public:

    int Count(long curr, long next, int n) {
        int countNum = 0;

        while(curr <= n) {
            countNum += (next - curr);

            curr *= 10;
            next *= 10;

            next = min(next, long(n+1));
        }

        return countNum;
    }

    int findKthNumber(int n, int k) {
        int curr = 1;
        k -= 1; //Since we start from the first number (1), we need k-1 more numbers

        while(k > 0) {
            int count = Count(curr, curr+1, n);
            if(count  <= k) {
                curr++;
                k -= count; //skipping the elements under curr prefix tree
            } else {
                curr *= 10;
                k -= 1;
            }
        }

        return curr;

    }
};
