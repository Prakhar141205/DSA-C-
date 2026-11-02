class Solution {
public:

    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        vector<int> ans(n);
        sort(begin(potions), end(potions));

        int maxPotion = potions[m-1];

        for(int i=0; i<n; i++) {
            int spell = spells[i];

            long long minPotion = ceil(1.0*success / spell) ;

            if(minPotion > maxPotion) {
                ans[i] = 0;
                continue;
            }

            auto idx = lower_bound(begin(potions), end(potions), minPotion) ;
            ans[i] = end(potions) - idx;
        }

        return ans;
    }
};


class Solution {
public:
    int apna_lower_bound(int l, int r, vector<int>& potions, long long minPotion) {
        int ans = -1;

        while(l <= r) {
            int m = l + (r-l)/2;

            if(potions[m] < minPotion) {
                l = m + 1;
            }else {
                ans = m;
                r = m -1 ;
            }
        }

        return ans;
    }
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        vector<int> ans(n);
        sort(begin(potions), end(potions));

        int maxPotion = potions[m-1];

        for(int i=0; i<n; i++) {
            int spell = spells[i];

            long long minPotion = ceil(1.0*success / spell) ;

            if(minPotion > maxPotion) {
                ans[i] = 0;
                continue;
            }

            auto idx = lower_bound(begin(potions), end(potions), minPotion) ;
            ans[i] = end(potions) - idx;
        }

        return ans;
    }
};


#include <bits/stdc++.h>
using namespace std;

/*
    LeetCode 2300. Successful Pairs of Spells and Potions

    A pair (spell, potion) succeeds when:
        spell * potion >= success

    Since spell > 0:
        potion >= ceil(success / spell)

    Compute the minimum required potion using integer arithmetic:
        required = (success + spell - 1) / spell

    All approaches below are independent. Rename the chosen class to
    Solution before submitting it to LeetCode.
*/


// -----------------------------------------------------------------------------
// Approach 1: Brute force
// Time: O(n * m), Space: O(1) auxiliary.
// Check every spell-potion pair directly.
// -----------------------------------------------------------------------------
class SolutionBruteForce {
public:
    vector<int> successfulPairs(vector<int>& spells,
                                vector<int>& potions,
                                long long success) {
        int n = (int)spells.size();
        vector<int> answer(n, 0);

        for (int i = 0; i < n; ++i) {
            for (int potion : potions) {
                if (1LL * spells[i] * potion >= success) {
                    ++answer[i];
                }
            }
        }
        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 2: Sort potions + custom lower_bound (manual binary search)
// Time: O(m log m + n log m), Space: O(log m) sorting stack (implementation
// dependent), plus O(1) auxiliary.
// Returns the first index whose potion value is >= required.
// If none exists, returns m.
// -----------------------------------------------------------------------------
class SolutionManualBinarySearch {
private:
    int firstAtLeast(const vector<int>& potions, long long required) {
        int left = 0;
        int right = (int)potions.size(); // Half-open interval [left, right).

        while (left < right) {
            int mid = left + (right - left) / 2;

            if ((long long)potions[mid] < required) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

public:
    vector<int> successfulPairs(vector<int>& spells,
                                vector<int>& potions,
                                long long success) {
        sort(potions.begin(), potions.end());

        int m = (int)potions.size();
        vector<int> answer;
        answer.reserve(spells.size());

        for (int spell : spells) {
            long long required = (success + spell - 1LL) / spell;
            int index = firstAtLeast(potions, required);
            answer.push_back(m - index);
        }
        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 3: Sort potions + STL lower_bound
// Time: O(m log m + n log m), Space: O(log m) sorting stack (implementation
// dependent), plus O(1) auxiliary.
// -----------------------------------------------------------------------------
class SolutionSTLLowerBound {
public:
    vector<int> successfulPairs(vector<int>& spells,
                                vector<int>& potions,
                                long long success) {
        sort(potions.begin(), potions.end());

        vector<int> answer;
        answer.reserve(spells.size());

        for (int spell : spells) {
            long long required = (success + spell - 1LL) / spell;

            auto it = lower_bound(
                potions.begin(), potions.end(), required
            );

            answer.push_back((int)(potions.end() - it));
        }
        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 4: Sort potions + upper_bound on the last failing potion
// Time: O(m log m + n log m), Space: O(log m) sorting stack (implementation
// dependent), plus O(1) auxiliary.
// Find the first potion strictly greater than required - 1.
// Since values are integers, this is equivalent to lower_bound(required).
// -----------------------------------------------------------------------------
class SolutionSTLUpperBound {
public:
    vector<int> successfulPairs(vector<int>& spells,
                                vector<int>& potions,
                                long long success) {
        sort(potions.begin(), potions.end());

        vector<int> answer;
        answer.reserve(spells.size());

        for (int spell : spells) {
            long long required = (success + spell - 1LL) / spell;

            auto it = upper_bound(
                potions.begin(), potions.end(), required - 1LL
            );

            answer.push_back((int)(potions.end() - it));
        }
        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 5: Offline sorting + two pointers
// Time: O(n log n + m log m), Space: O(n) for indexed spells.
// Sort spells in descending order. As spell strength decreases, the minimum
// required potion never decreases, so one pointer moves only to the right.
// -----------------------------------------------------------------------------
class SolutionTwoPointers {
public:
    vector<int> successfulPairs(vector<int>& spells,
                                vector<int>& potions,
                                long long success) {
        int n = (int)spells.size();
        int m = (int)potions.size();

        sort(potions.begin(), potions.end());

        vector<pair<int, int>> orderedSpells;
        orderedSpells.reserve(n);

        for (int i = 0; i < n; ++i) {
            orderedSpells.push_back({spells[i], i});
        }

        sort(orderedSpells.begin(), orderedSpells.end(),
             [](const auto& a, const auto& b) {
                 return a.first > b.first;
             });

        vector<int> answer(n);
        int potionIndex = 0;

        for (const auto& [spell, originalIndex] : orderedSpells) {
            long long required = (success + spell - 1LL) / spell;

            while (potionIndex < m &&
                   (long long)potions[potionIndex] < required) {
                ++potionIndex;
            }

            answer[originalIndex] = m - potionIndex;
        }

        return answer;
    }
};


// -----------------------------------------------------------------------------
// Approach 6: Frequency array + suffix counts (bounded-value approach)
// Time: O(m + U + n), Space: O(U), where U = maximum potion strength.
// Constraints guarantee potion strengths <= 1e5.
// Avoids sorting and binary search.
// -----------------------------------------------------------------------------
class SolutionFrequencyArray {
public:
    vector<int> successfulPairs(vector<int>& spells,
                                vector<int>& potions,
                                long long success) {
        int maxPotion = *max_element(potions.begin(), potions.end());

        // freq[x] = number of potions having strength exactly x.
        vector<int> suffixCount(maxPotion + 2, 0);

        for (int potion : potions) {
            ++suffixCount[potion];
        }

        // Convert frequencies into suffix counts:
        // suffixCount[x] = number of potions with strength >= x.
        for (int x = maxPotion - 1; x >= 1; --x) {
            suffixCount[x] += suffixCount[x + 1];
        }

        vector<int> answer;
        answer.reserve(spells.size());

        for (int spell : spells) {
            long long required = (success + spell - 1LL) / spell;

            if (required > maxPotion) {
                answer.push_back(0);
            } else {
                answer.push_back(suffixCount[(int)required]);
            }
        }

        return answer;
    }
};


/*
    Example 1:
        spells  = [5, 1, 3]
        potions = [1, 2, 3, 4, 5]
        success = 7

    Sort potions:
        [1, 2, 3, 4, 5]

    Spell = 5:
        required = ceil(7/5) = 2
        Successful potions = [2,3,4,5], count = 4

    Spell = 1:
        required = ceil(7/1) = 7
        No potion is strong enough, count = 0

    Spell = 3:
        required = ceil(7/3) = 3
        Successful potions = [3,4,5], count = 3

    Answer = [4,0,3]


    Important correction to common custom lower_bound implementations:
      It is convenient for binary search to return an insertion index in
      [0, m], rather than -1 when no valid element exists.
      Then the answer is always:
          m - insertionIndex

    Overflow:
      success can be as large as 1e10, so keep it as long long.
      Use 1LL * spell * potion if checking a product directly.
      The ceiling-division expression above is also evaluated as long long.

    Recommended submission:
      - Approach 3 (STL lower_bound): simplest and interview-friendly.
      - Approach 5 (two pointers): avoids one binary search per spell.
      - Approach 6 (frequency array): leverages the small potion-value bound.
*/
