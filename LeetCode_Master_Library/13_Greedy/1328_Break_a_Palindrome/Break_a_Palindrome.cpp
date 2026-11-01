/*
LeetCode 1328 — Break a Palindrome
Original source: Greedy Algorithm/1328. Break a Palindrome.cpp
Original source files: 1
Approaches implemented: 2
Recommended: SolutionGreedy

Approach index:
1. Exhaustive search over every one-character replacement
2. First-half lexicographic greedy
*/

#include <string>
using namespace std;

static bool isPalindrome(const string& s) {
    int left = 0, right = (int)s.size() - 1;
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

// 1. Exhaustive search.
// Time: O(26 * n^2); auxiliary space: O(n) for the returned candidate.
// Educational baseline; repeated palindrome checks make it slower.
class SolutionBruteForce {
public:
    string breakPalindrome(string palindrome) {
        const int n = (int)palindrome.size();
        if (n == 1) return "";

        string best;
        bool found = false;
        for (int i = 0; i < n; ++i) {
            const char original = palindrome[i];
            for (char replacement = 'a'; replacement <= 'z'; ++replacement) {
                if (replacement == original) continue;
                palindrome[i] = replacement;
                if (!isPalindrome(palindrome) &&
                    (!found || palindrome < best)) {
                    best = palindrome;
                    found = true;
                }
            }
            palindrome[i] = original;
        }
        return found ? best : "";
    }
};

// 2. Lexicographic greedy.
// Time: O(n); auxiliary space: O(1), excluding the by-value input string.
class SolutionGreedy {
public:
    string breakPalindrome(string palindrome) {
        const int n = (int)palindrome.size();
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
