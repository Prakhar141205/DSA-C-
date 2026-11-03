#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 1207 - Unique Number of Occurrences

    Return true iff every distinct value in arr has a different frequency.

    All classes below are independent. Rename the selected class to Solution
    before submitting it to LeetCode.
*/


// -----------------------------------------------------------------------------
// Approach 1: Brute force frequency counting
// Time: O(n^2); Space: O(n)
// For each element, count its occurrences and compare with the frequency of
// every distinct value. The set prevents checking the same value repeatedly.
// -----------------------------------------------------------------------------
class SolutionBruteForce {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_set<int> checked;

        for (int x : arr) {
            if (checked.count(x)) continue;
            checked.insert(x);

            int frequency = 0;
            for (int y : arr) {
                if (y == x) ++frequency;
            }

            for (int other : checked) {
                if (other == x) continue;

                int otherFrequency = 0;
                for (int y : arr) {
                    if (y == other) ++otherFrequency;
                }

                if (frequency == otherFrequency) return false;
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Sort + count consecutive groups + sort frequencies
// Time: O(n log n); Space: O(n) for the frequency list (sorting stack aside).
// Sorting groups equal values together. Then sort the resulting frequencies
// and check for adjacent duplicates.
// -----------------------------------------------------------------------------
class SolutionSorting {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        vector<int> frequencies;

        for (int i = 0; i < (int)arr.size();) {
            int j = i;
            while (j < (int)arr.size() && arr[j] == arr[i]) {
                ++j;
            }

            frequencies.push_back(j - i);
            i = j;
        }

        sort(frequencies.begin(), frequencies.end());

        for (int i = 1; i < (int)frequencies.size(); ++i) {
            if (frequencies[i] == frequencies[i - 1]) {
                return false;
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Ordered map + ordered set
// Time: O(n log k); Space: O(k), k = number of distinct values.
// The map counts each value. The set detects whether a frequency was already
// encountered. No separate sorting of the answer is needed.
// -----------------------------------------------------------------------------
class SolutionOrderedMapSet {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        map<int, int> frequency;

        for (int x : arr) {
            ++frequency[x];
        }

        set<int> seenFrequencies;

        for (const auto& [value, count] : frequency) {
            (void)value;

            if (!seenFrequencies.insert(count).second) {
                return false;
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 4: Unordered map + unordered set
// Average Time: O(n); Space: O(k).
// This is the standard hash-based solution.
// -----------------------------------------------------------------------------
class SolutionHashMapSet {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int, int> frequency;
        frequency.reserve(arr.size());

        for (int x : arr) {
            ++frequency[x];
        }

        unordered_set<int> seenFrequencies;
        seenFrequencies.reserve(frequency.size());

        for (const auto& [value, count] : frequency) {
            (void)value;

            if (!seenFrequencies.insert(count).second) {
                return false;
            }
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Fixed frequency array + fixed seen-frequency array
// Time: O(n + R); Space: O(R), R = 2001.
// Uses the given value range [-1000, 1000]. A frequency can be at most n.
// -----------------------------------------------------------------------------
class SolutionFrequencyArrays {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        const int OFFSET = 1000;
        const int RANGE = 2001;
        const int MAX_N = 1000;

        int frequency[RANGE] = {};
        bool seen[MAX_N + 1] = {};

        for (int x : arr) {
            ++frequency[x + OFFSET];
        }

        for (int count : frequency) {
            if (count == 0) continue;

            if (seen[count]) return false;
            seen[count] = true;
        }

        return true;
    }
};


// -----------------------------------------------------------------------------
// Approach 6: Fixed frequency array + sort only nonzero frequencies
// Time: O(n + R + k log k); Space: O(R + k).
// A variation of the user's frequency-array idea. Compare actual occurrence
// counts, not adjacent slots in the value-frequency array.
// -----------------------------------------------------------------------------
class SolutionFrequencyArraySort {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        const int OFFSET = 1000;
        const int RANGE = 2001;

        int frequency[RANGE] = {};
        for (int x : arr) {
            ++frequency[x + OFFSET];
        }

        vector<int> counts;
        for (int count : frequency) {
            if (count > 0) counts.push_back(count);
        }

        sort(counts.begin(), counts.end());

        for (int i = 1; i < (int)counts.size(); ++i) {
            if (counts[i] == counts[i - 1]) return false;
        }

        return true;
    }
};


/*
    Example 1:
      arr = [1,2,2,1,1,3]

      value 1 -> frequency 3
      value 2 -> frequency 2
      value 3 -> frequency 1

      Frequencies = [3,2,1] -> all distinct -> true.

    Example 2:
      arr = [1,2]

      value 1 -> frequency 1
      value 2 -> frequency 1

      Frequencies = [1,1] -> duplicate -> false.

    Important note about the submitted solution:
      Your code compares nums[i] with nums[i-1], where i and i-1 are
      neighboring VALUE slots after applying the offset. Those slots
      represent different input values, but their occurrence counts can
      match even when the values are not adjacent.

      Example: arr = [1,1,1,3,3]
        frequency of 1 = 3
        frequency of 3 = 2
      The nonzero counts are distinct, but the relevant frequency slots
      are separated by an empty slot. Your adjacent-slot check misses
      this comparison.

      Instead, use a separate seen[count] array (Approach 5), or collect
      all nonzero counts and check them for duplicates.

    Recommended:
      - Approach 5 for these exact constraints: O(n + 2001), simple and fast.
      - Approach 4 for a general-purpose hash-based solution.
*/
