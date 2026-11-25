
/*
    ============================================================
    APPROACH 1: BRUTE FORCE (TRY ALL POSSIBLE PAIRS)
    ============================================================

    T.C : O(n^2)
    S.C : O(n)

    APPROACH:
    1. Maintain a boolean array to track used elements.
    2. For every unused element, search for another unused
       element whose sum with it is divisible by k.
    3. If no matching element is found, return false.
    4. If every element gets paired, return true.

    ============================================================
    APPROACH 2: USING HASHSET (REMAINDER MATCHING)
    ============================================================

    T.C : O(n) average
    S.C : O(n)

    APPROACH:
    1. Calculate the remainder of every element using k.
    2. Find the complementary remainder required to make
       their sum divisible by k.
    3. If the complementary remainder exists in the set,
       form a pair and remove both remainders.
    4. Otherwise, insert the current remainder into the set.
    5. If the set is empty at the end, all elements are paired.

    ============================================================
    MATHEMATICAL PROOF: WHY REMAINDER MATCHING WORKS
    ============================================================

    We need to divide the array into pairs such that:

                    (a + b) % k == 0

    Let:

        a % k = r1
        b % k = r2

    For their sum to be divisible by k:

        (r1 + r2) % k = 0

    Therefore:

        r1 + r2 = k   OR   r1 + r2 = 0

    For non-negative numbers, the possible cases are:

        Case 1: Both remainders are 0.
                (0 + 0) % k = 0

        Case 2: Remainders are complementary.
                (r + (k-r)) % k = 0

    Example: k = 5

        Remainder 0 -> Required remainder 0
        Remainder 1 -> Required remainder 4
        Remainder 2 -> Required remainder 3
        Remainder 3 -> Required remainder 2
        Remainder 4 -> Required remainder 1

    Thus, we only need to find complementary remainders.

    WHY HASHSET?

    The set stores remainders that are waiting for a match.

    If the required remainder is already present:
        - A valid pair is formed.
        - Remove both remainders.

    Otherwise:
        - Insert the current remainder for future matching.

    At the end:
        Empty set     -> All elements are paired.
        Non-empty set -> Some elements remain unpaired.

    NOTE:
    The HashSet approach assumes non-negative array elements.
    For a fully robust implementation with arbitrary duplicate
    remainders, use a remainder-frequency array (Approach 3).
*/


#include <bits/stdc++.h>
using namespace std;


/* ============================================================
   APPROACH 1: BRUTE FORCE (TRY ALL POSSIBLE PAIRS)
   ============================================================ */

// T.C : O(n^2)
// S.C : O(n)

class Solution1 {
public:
    bool canPair(vector<int> nums, int k) {

        int n = nums.size();

        // Track whether an element is already used in a pair.
        // T.C : O(n)
        vector<bool> used(n, false);

        // Traverse every element.
        // T.C : O(n)
        for (int i = 0; i < n; i++) {

            // Skip elements that are already paired.
            // T.C : O(1)
            if (used[i]) {
                continue;
            }

            bool foundPair = false;

            // Find another unused element that forms
            // a valid pair with nums[i].
            // T.C : O(n) for each i.
            // Overall nested loop: O(n^2)
            for (int j = i + 1; j < n; j++) {

                // Check whether both elements are unused
                // and their sum is divisible by k.
                if (!used[j] && (nums[i] + nums[j]) % k == 0) {

                    // Mark both elements as used.
                    used[i] = true;
                    used[j] = true;

                    foundPair = true;
                    break;
                }
            }

            // If no matching pair is found, return false.
            if (!foundPair) {
                return false;
            }
        }

        // Every element has been successfully paired.
        return true;
    }
};


/* ============================================================
   APPROACH 2: USING HASHSET (REMAINDER MATCHING)
   ============================================================ */

// T.C : O(n) average
// S.C : O(n)

class Solution2 {
public:
    bool canPair(vector<int> nums, int k) {

        int n = nums.size();

        // An odd number of elements cannot be divided into pairs.
        // T.C : O(1)
        if (n % 2 != 0) {
            return false;
        }

        // Store remainders that are waiting for their
        // complementary remainder.
        // S.C : O(n)
        unordered_set<int> st;

        // Process every element.
        // T.C : O(n) average
        for (int i = 0; i < n; i++) {

            // Calculate the remainder of the current element.
            // T.C : O(1)
            int remain = nums[i] % k;

            // Calculate the complementary remainder.
            // T.C : O(1)
            int other_remain = (k - remain) % k;

            // Check whether the required remainder is available.
            // Special case: remainder 0 needs another remainder 0.
            // Average T.C : O(1)
            if (st.find(other_remain) != st.end()) {

                // A valid pair has been found.
                // Remove the matched remainder.
                // Average T.C : O(1)
                st.erase(other_remain);
            }
            else {

                // No matching remainder is available.
                // Store the current remainder.
                // Average T.C : O(1)
                st.insert(remain);
            }
        }

        // If no unmatched remainder is left, pairing is successful.
        // T.C : O(1)
        return st.empty();
    }
};


/* ============================================================
   APPROACH 3: USING REMAINDER FREQUENCY ARRAY
   ============================================================ */

// T.C : O(n + k)
// S.C : O(k)
//
// This is the robust remainder-frequency approach.
// It handles duplicate remainders correctly.

class Solution3 {
public:
    bool canPair(vector<int> nums, int k) {

        int n = nums.size();

        // An odd number of elements cannot form complete pairs.
        // T.C : O(1)
        if (n % 2 != 0) {
            return false;
        }

        // Store the frequency of every possible remainder.
        // Possible remainders: 0 to k-1.
        // T.C : O(k)
        // S.C : O(k)
        vector<int> freq(k, 0);

        // Calculate remainder frequency for every element.
        // T.C : O(n)
        for (int num : nums) {

            // Normalize remainder to handle negative numbers.
            int remain = ((num % k) + k) % k;

            freq[remain]++;
        }

        // Case 1:
        // Elements with remainder 0 must be paired together.
        // Therefore, their frequency must be even.
        // T.C : O(1)
        if (freq[0] % 2 != 0) {
            return false;
        }

        // Case 2:
        // Remainder r must have the same frequency
        // as its complementary remainder (k-r).
        //
        // Example: k = 5
        // freq[1] must equal freq[4].
        // freq[2] must equal freq[3].
        //
        // T.C : O(k)
        for (int i = 1; i <= k / 2; i++) {

            // Special case:
            // When k is even, remainder k/2 pairs with itself.
            // Its frequency must be even.
            if (i == k - i) {

                if (freq[i] % 2 != 0) {
                    return false;
                }
            }

            // Normal complementary remainder case.
            else {

                if (freq[i] != freq[k - i]) {
                    return false;
                }
            }
        }

        // All remainder frequencies satisfy pairing conditions.
        return true;
    }
};
