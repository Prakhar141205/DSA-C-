/*
    LeetCode 779. K-th Symbol in Grammar
    ====================================
    Given row n and 1-indexed position k, return the symbol at that position.

    Rule:
      0 -> 01
      1 -> 10

    Constraints: 1 <= n <= 30, 1 <= k <= 2^(n-1).

    Approaches included:
      1. Brute force: build the complete row
      2. Recursive position reduction
      3. Iterative position reduction
      4. Bit-count / parity trick
      5. Recursive bit-count solution
      6. Recursive row-property solution

    Each approach has its own class so all can coexist in one file.
*/

#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------------------------------------
// Approach 1: Brute force — construct every row as a string.
//
// For every character in the previous row:
//   '0' contributes "01"
//   '1' contributes "10"
//
// This corrects the common mistake of appending reverse(previousRow).
//
// Time:  O(2^n) total character work
// Space: O(2^n) for the generated row (plus temporary strings)
// Practical only for small n.
// --------------------------------------------------------------------------
class SolutionBruteForce {
public:
    int kthGrammar(int n, int k) {
        string row = "0";

        for (int level = 2; level <= n; ++level) {
            string next;
            next.reserve(row.size() * 2);

            for (char bit : row) {
                if (bit == '0') {
                    next += "01";
                } else {
                    next += "10";
                }
            }

            row = move(next);
        }

        return row[k - 1] - '0';
    }
};

// --------------------------------------------------------------------------
// Approach 2: Recursive position reduction.
//
// The row is formed as:
//   previousRow + complement(previousRow)
//
// Therefore:
//   - If k is in the first half (k <= 2^(n-2)), it is the same symbol
//     as position k in row n-1.
//   - Otherwise, it is the complement of position k - 2^(n-2)
//     in row n-1.
//
// Equivalent, simpler positional recurrence:
//   parent position = ceil(k / 2) = (k + 1) / 2
//   if k is even, current symbol = complement(parent symbol)
//   if k is odd,  current symbol = parent symbol
//
// Time:  O(n)
// Space: O(n) recursion stack.
// --------------------------------------------------------------------------
class SolutionRecursive {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) return 0;

        int parent = kthGrammar(n - 1, (k + 1) / 2);

        if (k % 2 == 0) {
            return 1 - parent;
        }
        return parent;
    }
};

// --------------------------------------------------------------------------
// Approach 3: Iterative position reduction.
//
// Follow the same parent relation without recursion. Every even position
// contributes one flip; odd positions contribute no flip.
//
// Time:  O(n)
// Space: O(1)
// --------------------------------------------------------------------------
class SolutionIterative {
public:
    int kthGrammar(int n, int k) {
        int flips = 0;

        while (n > 1) {
            if (k % 2 == 0) {
                ++flips;
            }

            k = (k + 1) / 2;
            --n;
        }

        return flips % 2;
    }
};

// --------------------------------------------------------------------------
// Approach 4: Bit-count / parity trick.
//
// The symbol at position k is the parity of the number of set bits in k-1:
//
//   answer = popcount(k - 1) % 2
//
// Examples:
//   k = 1 -> k-1 = 0  -> 0 set bits -> 0
//   k = 2 -> k-1 = 1  -> 1 set bit  -> 1
//   k = 3 -> k-1 = 2  -> 1 set bit  -> 1
//   k = 4 -> k-1 = 3  -> 2 set bits -> 0
//
// Time:  O(log k) using a simple bit loop; O(1) machine-word operations
//       with a compiler popcount intrinsic.
// Space: O(1)
// --------------------------------------------------------------------------
class SolutionBitCount {
public:
    int kthGrammar(int n, int k) {
        (void)n; // n is not needed once k is valid.
        return __builtin_popcount((unsigned int)(k - 1)) % 2;
    }
};

// Portable alternative to Approach 4 (does not use compiler intrinsics).
class SolutionBitCountPortable {
public:
    int kthGrammar(int n, int k) {
        (void)n;
        unsigned int x = (unsigned int)(k - 1);
        int parity = 0;

        while (x > 0) {
            parity ^= (x & 1U);
            x >>= 1;
        }

        return parity;
    }
};

// --------------------------------------------------------------------------
// Approach 5: Recursive bit-count solution.
//
// Count the set bits of k-1 recursively. Each set bit toggles the answer.
//
// Time:  O(log k)
// Space: O(log k) recursion stack.
// --------------------------------------------------------------------------
class SolutionRecursiveBitCount {
private:
    int parity(unsigned int x) {
        if (x == 0) return 0;
        return (x & 1U) ^ parity(x >> 1);
    }

public:
    int kthGrammar(int n, int k) {
        (void)n;
        return parity((unsigned int)(k - 1));
    }
};

// --------------------------------------------------------------------------
// Approach 6: Recursive row-property solution.
//
// In each row, the second half is the complement of the first half.
// If k lies in the second half, move to the corresponding position in the
// first half and toggle the answer.
//
// Time:  O(n)
// Space: O(n) recursion stack.
// --------------------------------------------------------------------------
class SolutionHalfRowRecursion {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) return 0;

        int halfLength = 1 << (n - 2);

        if (k <= halfLength) {
            return kthGrammar(n - 1, k);
        }

        return 1 - kthGrammar(n - 1, k - halfLength);
    }
};

class Solution {
public:

    
    int kthGrammar(int n, int k) {
        if(n == 1 and k == 1) return 0;

        int length = pow(2, n-1);
        int mid = length / 2;

        if(k <= mid) {
            return kthGrammar(n-1, k);
        }

        return !kthGrammar(n-1, k-mid);

    }
};

/*
    Complexity summary
    ------------------------------------------------------------------------
    Approach                           Time             Auxiliary space
    ------------------------------------------------------------------------
    1. Build the complete row          O(2^n)           O(2^n)
    2. Recursive position reduction    O(n)             O(n)
    3. Iterative position reduction    O(n)             O(1)
    4. Bit-count / parity              O(log k)*         O(1)
    5. Recursive bit-count             O(log k)          O(log k)
    6. Recursive half-row property     O(n)              O(n)

    *With __builtin_popcount, this is a constant number of machine-word
     operations for the given integer type; the portable loop is O(log k).

    Recommended LeetCode submission:
      SolutionBitCount, or SolutionIterative if you want to derive the answer
      directly from the grammar's parent-child relationship.

    Key insight:
      kthGrammar(n, k) = popcount(k - 1) % 2.

    Why k-1?
      The positions are 1-indexed, while the binary path to a symbol is
      represented naturally by the zero-indexed position k-1. Each 1 bit
      corresponds to entering a complemented half, toggling the symbol.
*/
