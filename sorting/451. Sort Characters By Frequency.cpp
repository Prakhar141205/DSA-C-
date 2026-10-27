#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 451 — Sort Characters By Frequency
(Your function name: frequencySort)

This file combines the approaches from your snippets and adds a few useful
alternatives. All approaches are methods of one Solution class so the file
can be copied as a single unit.

Approaches:
1. Sort string, then count consecutive characters
2. unordered_map + vector + custom sort
3. Frequency buckets using unordered_map
4. Priority queue (max-heap) using unordered_map
5. Bounded ASCII frequency array + max-heap
6. Bounded ASCII frequency array + frequency buckets
7. Ordered map + vector + custom sort
8. Sort distinct characters using a custom comparator that reads a frequency table

Assumption for bounded-ASCII approaches:
The input contains standard ASCII characters (character codes 0..127).
Approaches 1–4 and 7 work with ordinary char values without needing a fixed
ASCII table. LeetCode 451's input is generally English letters.
*/

class Solution {
public:
    // ---------------------------------------------------------------
    // Approach 1: Sort the string, then group equal consecutive chars.
    // Time: O(n log n + k log k), Space: O(k) besides sort's stack.
    // n = s.size(), k = number of distinct characters.
    // ---------------------------------------------------------------
    string frequencySortSortAndGroup(string s) {
        sort(s.begin(), s.end());

        int n = (int)s.size();
        int i = 0;
        vector<pair<char, int>> freq;

        while (i < n) {
            char c = s[i];
            int count = 0;

            while (i < n && s[i] == c) {
                ++count;
                ++i;
            }

            freq.push_back({c, count});
        }

        // Sort characters by descending frequency.
        // Equal-frequency characters may appear in any order.
        sort(freq.begin(), freq.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        string answer;
        answer.reserve(s.size());

        for (const auto& [c, count] : freq) {
            answer += string(count, c);
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 2: unordered_map + vector + custom comparator.
    // Time: O(n + k log k), Space: O(n + k).
    // ---------------------------------------------------------------
    string frequencySortHashMapSort(string s) {
        unordered_map<char, int> freq;
        for (char c : s) {
            ++freq[c];
        }

        vector<pair<char, int>> chars(freq.begin(), freq.end());

        sort(chars.begin(), chars.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        string answer;
        answer.reserve(s.size());

        for (const auto& [c, count] : chars) {
            answer += string(count, c);
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 3: Frequency buckets.
    // bucket[f] stores each distinct character whose frequency is f.
    // Then scan frequencies from high to low.
    // Time: O(n + k + n) = O(n), expected with unordered_map.
    // Space: O(n + k).
    // ---------------------------------------------------------------
    string frequencySortBuckets(string s) {
        unordered_map<char, int> freq;
        for (char c : s) {
            ++freq[c];
        }

        vector<string> bucket(s.size() + 1);

        for (const auto& [c, count] : freq) {
            bucket[count] += c;
        }

        string answer;
        answer.reserve(s.size());

        for (int count = (int)s.size(); count >= 1; --count) {
            for (char c : bucket[count]) {
                answer += string(freq[c], c);
            }
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 4: Max-heap / priority_queue.
    // pair<int, char> orders primarily by frequency, then by character.
    // Time: O(n + k log k), Space: O(n + k).
    // ---------------------------------------------------------------
    string frequencySortMaxHeap(string s) {
        unordered_map<char, int> freq;
        for (char c : s) {
            ++freq[c];
        }

        priority_queue<pair<int, char>> pq;
        for (const auto& [c, count] : freq) {
            pq.push({count, c});
        }

        string answer;
        answer.reserve(s.size());

        while (!pq.empty()) {
            auto [count, c] = pq.top();
            pq.pop();
            answer += string(count, c);
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 5: Bounded ASCII frequency array + max-heap.
    // ASCII codes are 0..127. This avoids hashing.
    // Time: O(n + A + k log k), Space: O(A + k), A = 128.
    // ---------------------------------------------------------------
    string frequencySortAsciiHeap(string s) {
        constexpr int A = 128;
        int freq[A] = {};

        for (unsigned char c : s) {
            if (c < A) {
                ++freq[c];
            } else {
                // This method is designed for ASCII input.
                // For non-ASCII bytes, use frequencySortMaxHeap instead.
                return frequencySortMaxHeap(s);
            }
        }

        priority_queue<pair<int, int>> pq;
        for (int c = 0; c < A; ++c) {
            if (freq[c] > 0) {
                pq.push({freq[c], c});
            }
        }

        string answer;
        answer.reserve(s.size());

        while (!pq.empty()) {
            auto [count, c] = pq.top();
            pq.pop();
            answer += string(count, (char)c);
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 6: Bounded ASCII frequency array + buckets.
    // bucket[f] stores ASCII characters with frequency f.
    // Time: O(n + A + n) = O(n), A = 128.
    // Space: O(n + A).
    // ---------------------------------------------------------------
    string frequencySortAsciiBuckets(string s) {
        constexpr int A = 128;
        vector<int> freq(A, 0);

        for (unsigned char c : s) {
            if (c >= A) {
                return frequencySortBuckets(s);
            }
            ++freq[c];
        }

        vector<string> bucket(s.size() + 1);
        for (int c = 0; c < A; ++c) {
            if (freq[c] > 0) {
                bucket[freq[c]].push_back((char)c);
            }
        }

        string answer;
        answer.reserve(s.size());

        for (int count = (int)s.size(); count >= 1; --count) {
            for (char c : bucket[count]) {
                answer += string(freq[(unsigned char)c], c);
            }
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 7: ordered map + vector + custom sort.
    // map sorts by character, not by frequency; the vector is then sorted
    // by frequency. This is deterministic but usually slower than hashing.
    // Time: O(n log k + k log k), Space: O(k + n).
    // ---------------------------------------------------------------
    string frequencySortOrderedMap(string s) {
        map<char, int> freq;
        for (char c : s) {
            ++freq[c];
        }

        vector<pair<char, int>> chars(freq.begin(), freq.end());

        sort(chars.begin(), chars.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        string answer;
        answer.reserve(s.size());

        for (const auto& [c, count] : chars) {
            answer += string(count, c);
        }

        return answer;
    }

    // ---------------------------------------------------------------
    // Approach 8: Sort the original characters with a frequency comparator.
    // This is a compact alternative, but sorting n characters costs O(n log n).
    // The comparator uses a precomputed frequency table.
    // Time: O(n + n log n), Space: O(A) auxiliary, excluding sort stack.
    // ASCII input is assumed.
    // ---------------------------------------------------------------
    string frequencySortComparator(string s) {
        constexpr int A = 128;
        vector<int> freq(A, 0);

        for (unsigned char c : s) {
            if (c >= A) {
                return frequencySortMaxHeap(s);
            }
            ++freq[c];
        }

        sort(s.begin(), s.end(), [&](char a, char b) {
            unsigned char ua = static_cast<unsigned char>(a);
            unsigned char ub = static_cast<unsigned char>(b);

            if (freq[ua] != freq[ub]) {
                return freq[ua] > freq[ub];
            }
            return ua < ub; // Tie-break consistently by character code.
        });

        return s;
    }

    // Required LeetCode method. Change the called method to compare approaches.
    string frequencySort(string s) {
        return frequencySortBuckets(s);
    }
};

/*
Examples:
Input:  "tree"      -> "eert" or "eetr"
Input:  "cccaaa"    -> "aaaccc" or "cccaaa"
Input:  "Aabb"      -> "bbAa" or "bbaA" (depending on frequency/tie order)

Notes:
- The exact order of characters with equal frequencies is not important.
- Do not print debug output in the LeetCode solution.
- string(count, c) creates a string containing c repeated count times.
- For general Unicode text, char/ASCII frequency approaches are not sufficient;
  use a Unicode-aware representation.
*/
