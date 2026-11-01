/*
LeetCode 1328 — Break a Palindrome
Comprehensive C++ solution variations

Task:
Change exactly one character of a palindromic lowercase string so that the
result is not a palindrome and is lexicographically smallest.
Return "" when impossible.

KEY OBSERVATION
For n == 1, no valid answer exists.

For n > 1:
1. Scan only the first half: indices [0, n/2).
2. Find the first character that is not 'a'.
3. Change it to 'a' and return immediately.
4. If every character in the first half is already 'a', the palindrome
   must consist entirely of 'a'. Change the last character to 'b'.

Why only the first half?
Changing a character in the first half has an earlier lexicographic impact
than changing its mirrored character in the second half. The middle
character of an odd-length palindrome cannot break the palindrome because
it mirrors itself.

Included approaches:
1. Exhaustive brute force: try every index and every replacement letter.
2. Brute force by position: for each index, try replacements in lexical order.
3. Enumerate only first-half candidates plus the final-character fallback.
4. Greedy first-half scan — canonical O(n) solution.
5. Greedy using find_if / iterator style.
6. Explicit two-pointer mirror scan — same greedy logic, different traversal.

Approaches 1–3 are intentionally slower reference solutions.
Approaches 4–6 are O(n) time and O(1) auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

// Helper used by brute-force approaches.
static bool isPalindromeString(const string& s) {
    int i = 0, j = (int)s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        ++i;
        --j;
    }
    return true;
}

// -----------------------------------------------------------------------------
// 1. FULL EXHAUSTIVE BRUTE FORCE
// Try every different lowercase replacement at every position. Keep the
// lexicographically smallest candidate that is not a palindrome.
//
// Time: O(26 * n^2) — O(n) candidate construction/check per replacement.
// Space: O(n) for the candidate string.
// -----------------------------------------------------------------------------
class Solution1_FullBruteForce {
public:
    string breakPalindrome(string palindrome) {
        int n = (int)palindrome.size();
        if (n == 1) return "";

        string best = "";
        bool found = false;

        for (int i = 0; i < n; ++i) {
            char original = palindrome[i];

            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (ch == original) continue; // Must actually change a char.

                palindrome[i] = ch;

                if (!isPalindromeString(palindrome)) {
                    if (!found || palindrome < best) {
                        best = palindrome;
                        found = true;
                    }
                }
            }

            palindrome[i] = original;
        }

        return found ? best : "";
    }
};

// -----------------------------------------------------------------------------
// 2. BRUTE FORCE BY POSITION, EARLY EXIT ON FIRST VALID LETTER
// For each index from left to right, try replacement letters from 'a' to 'z'.
// The first valid replacement at the earliest position is globally smallest.
//
// Time: O(26 * n^2) worst case.
// Space: O(n).
// This still performs repeated palindrome checks, but avoids comparing all
// valid candidates after the earliest valid position has been found.
// -----------------------------------------------------------------------------
class Solution2_PositionFirstBruteForce {
public:
    string breakPalindrome(string palindrome) {
        int n = (int)palindrome.size();
        if (n == 1) return "";

        for (int i = 0; i < n; ++i) {
            char original = palindrome[i];

            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (ch == original) continue;

                palindrome[i] = ch;

                if (!isPalindromeString(palindrome)) {
                    return palindrome;
                }
            }

            palindrome[i] = original;
        }

        return "";
    }
};

// -----------------------------------------------------------------------------
// 3. RESTRICTED EXHAUSTIVE SEARCH USING THE PALINDROME STRUCTURE
// Only test changes in the first half. If none of those changes can produce
// a lexicographically smaller valid string, change the final character to 'b'.
//
// At each first-half position, try 'a' first. If the original character is
// already 'a', try higher letters until a non-palindrome is produced.
//
// Time: O(26 * n^2) worst case with full palindrome checks.
// Space: O(n).
// -----------------------------------------------------------------------------
class Solution3_FirstHalfBruteForce {
public:
    string breakPalindrome(string palindrome) {
        int n = (int)palindrome.size();
        if (n == 1) return "";

        for (int i = 0; i < n / 2; ++i) {
            char original = palindrome[i];

            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (ch == original) continue;

                palindrome[i] = ch;
                if (!isPalindromeString(palindrome)) {
                    return palindrome;
                }
            }

            palindrome[i] = original;
        }

        // If first half has no useful change, the string is all 'a'.
        // Changing the last character to 'b' breaks the palindrome.
        palindrome[n - 1] = 'b';
        return palindrome;
    }
};

// -----------------------------------------------------------------------------
// 4. OPTIMAL GREEDY — CANONICAL SOLUTION
// Time: O(n), Space: O(1) auxiliary.
// -----------------------------------------------------------------------------
class Solution4_Greedy {
public:
    string breakPalindrome(string palindrome) {
        int n = (int)palindrome.size();

        if (n == 1) return "";

        for (int i = 0; i < n / 2; ++i) {
            if (palindrome[i] != 'a') {
                palindrome[i] = 'a';
                return palindrome;
            }
        }

        palindrome[n - 1] = 'b';
        return palindrome;
    }
};

// -----------------------------------------------------------------------------
// 5. GREEDY USING find_if
// Same O(n) algorithm, expressed with an STL search.
// Time: O(n), Space: O(1) auxiliary.
// -----------------------------------------------------------------------------
class Solution5_FindIfGreedy {
public:
    string breakPalindrome(string palindrome) {
        int n = (int)palindrome.size();
        if (n == 1) return "";

        auto it = find_if(palindrome.begin(),
                          palindrome.begin() + n / 2,
                          [](char ch) { return ch != 'a'; });

        if (it != palindrome.begin() + n / 2) {
            *it = 'a';
        } else {
            palindrome[n - 1] = 'b';
        }

        return palindrome;
    }
};

// -----------------------------------------------------------------------------
// 6. TWO-POINTER / MIRROR-AWARE GREEDY
// Move inward from both ends, but only modify the left-side character.
// The right pointer is maintained to make the mirrored structure explicit.
// Time: O(n), Space: O(1) auxiliary.
// -----------------------------------------------------------------------------
class Solution6_TwoPointerGreedy {
public:
    string breakPalindrome(string palindrome) {
        int n = (int)palindrome.size();
        if (n == 1) return "";

        int left = 0;
        int right = n - 1;

        while (left < right) {
            if (palindrome[left] != 'a') {
                palindrome[left] = 'a';
                return palindrome;
            }

            ++left;
            --right;
        }

        // All mirrored positions in the first half were 'a'.
        palindrome[n - 1] = 'b';
        return palindrome;
    }
};

/*
GREEDY CORRECTNESS — WHY THIS WORKS

Case 1: There is a non-'a' character in the first half.
Let i be the first such index.
- Every earlier character is already 'a', the smallest possible lowercase
  character, so no earlier position can be made lexicographically smaller.
- Replacing palindrome[i] with 'a' is the smallest possible character change
  at the earliest position where a decrease is possible.
- Since its mirrored character at n-1-i remains unchanged, the resulting
  string is no longer a palindrome.
Therefore this is the lexicographically smallest valid result.

Case 2: Every character in the first half is 'a'.
Because the input is a palindrome, its second half is also all 'a'; for odd
length, the middle character is also 'a'. Thus the entire string is all 'a'.
Changing the final character to 'b' breaks the palindrome while preserving
the longest possible prefix of 'a', so it is lexicographically smallest.

Why not change the middle character?
For odd n, the middle character mirrors itself. Changing it alone preserves
the palindrome, so it cannot be the required operation.

COMPLEXITY SUMMARY
1. Full exhaustive brute force      O(26*n^2)  O(n)
2. Position-first brute force        O(26*n^2)  O(n)
3. First-half exhaustive search      O(26*n^2)  O(n)
4. Greedy                            O(n)       O(1)
5. find_if greedy                    O(n)       O(1)
6. Two-pointer greedy                O(n)       O(1)

RECOMMENDED SUBMISSION
Use Solution4_Greedy. It is the simplest optimal implementation.

Your submitted code is already correct. Its key details are:
- `i < n/2`: inspect only the first half, excluding the middle.
- Change the first non-'a' to 'a' and return immediately.
- If no such character exists, change the last character to 'b'.
*/
