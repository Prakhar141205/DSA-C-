# LeetCode 1328 — Break a Palindrome

- **Original:** [`Greedy Algorithm/1328. Break a Palindrome.cpp`](../../../Greedy%20Algorithm/1328.%20Break%20a%20Palindrome.cpp)
- **Original submissions:** 1
- **Approaches:** 2
- **Recommended:** [SolutionGreedy](./Break_a_Palindrome.cpp)

## Problem

Change exactly one lowercase letter in a palindromic string so the result
is not a palindrome, and return the lexicographically smallest valid result.
For a one-character input, return the empty string because changing its
only character leaves a palindrome.

## 1. Exhaustive replacement search

Try each index and each replacement letter other than its current letter.
For each candidate, check whether it remains a palindrome and retain the
lexicographically smallest non-palindrome.

This is complete because every allowed answer differs at exactly one
position, and the loops enumerate all such candidates. For length `n`,
there are at most `26n` candidates and each palindrome test takes `O(n)`,
giving `O(26n^2)` time. The candidate string takes `O(n)` space.

**Dry run:** For `"aba"`, changing index 0 to `a` does nothing (skipped);
changing it to `b` yields `"bba"`, a valid candidate. Trying the other
positions and letters cannot beat the smallest valid candidate found.

**Use/limits:** A useful correctness baseline, but unnecessarily repeats
full string scans. The empty result for length one is handled explicitly.

## 2. First-half greedy

Scan indices `[0, n/2)`. Change the first character not equal to `'a'` to
`'a'` and return. If none exists, change the final character to `'b'`.

### Why it works

An earlier character dominates all later positions in lexicographic order.
The first-half scan finds the earliest position that can be decreased.
Changing it to the smallest alphabet character improves the result and
breaks the mirrored equality. For odd lengths the middle character mirrors
itself, so changing only the middle cannot break the palindrome.

If the entire first half is `'a'`, palindromicity forces the entire string
to be all `'a'` (including the center, when present). Changing the last
character to `'b'` is then the smallest possible valid change because it
preserves the longest all-`'a'` prefix.

**Dry run:** `"egcfe"` has first-half characters `e,g`. Change the first
non-`'a'` (`e`) to `a`; result `"agcfe"` is not a palindrome and is
lexicographically minimal. For `"aaaa"`, no first-half change applies, so
the result is `"aaab"`.

Time is `O(n)` from the scan; auxiliary space is `O(1)` beyond the
by-value string returned by the LeetCode signature.

## Original submission analysis

The original file has six versions: full exhaustive search, position-first
search, first-half restricted search, canonical greedy, `find_if` greedy,
and a mirror-aware two-pointer traversal. The greedy variants implement
the same decision rule; the exhaustive variants provide the correctness
baseline. The reference consolidates those into the two algorithmically
distinct ideas to avoid cosmetic duplication. No original file is modified.

## Comparison and review

| Approach | Time | Auxiliary space | Constraint suitability |
|---|---:|---:|---|
| Exhaustive replacements | `O(26n^2)` | `O(n)` | Correct but slower |
| First-half greedy | `O(n)` | `O(1)` | Recommended |

**Edge cases:** length one; all `'a'`; first non-`'a'` at index zero;
odd-length strings where the middle character must not be changed.

**Common mistake:** changing the middle character of an odd palindrome
does not make it non-palindromic.

**Follow-ups:** Prove the lexicographic choice; return the index and
replacement character instead of a new string; adapt the alphabet or
minimize under a different ordering.

## Validation status

Compiled as C++17 and differentially checked against exhaustive search on
small palindrome inputs, including single-character, all-`'a'`, even- and
odd-length cases.
