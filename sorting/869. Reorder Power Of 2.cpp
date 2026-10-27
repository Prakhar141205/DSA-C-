#include <bits/stdc++.h>
using namespace std;

/*
LeetCode 869 — Reordered Power of 2

Required signature:
    bool reorderedPowerOf2(int n)

Approaches included:
1. Sort digits and compare against every power of two
2. Digit-frequency counting and compare against every power of two
3. Precomputed digit signatures for all powers of two
4. Backtracking / permutation generation (avoid leading zero)
5. Digit DP-style frequency signature lookup

For n <= 10^9, powers of two up to 2^30 are sufficient because
2^30 = 1,073,741,824 and 2^31 > 10^9.
Approaches 1 and 2 are the simplest recommended solutions.
*/

class Solution {
private:
    // Returns the digits of x in ascending order.
    string sortedDigits(int x) {
        string s = to_string(x);
        sort(s.begin(), s.end());
        return s;
    }

    // Returns the frequency of each decimal digit 0..9.
    array<int, 10> digitCount(int x) {
        array<int, 10> freq{};
        while (x > 0) {
            ++freq[x % 10];
            x /= 10;
        }
        return freq;
    }

    // Helper for Approach 4: generate permutations without leading zero.
    bool buildPermutations(string& digits, vector<bool>& used,
                           long long value, int chosen, int targetLength) {
        if (chosen == targetLength) {
            if (value > INT_MAX) return false;
            int x = (int)value;
            return x > 0 && (x & (x - 1)) == 0;
        }

        for (int i = 0; i < (int)digits.size(); ++i) {
            if (used[i]) continue;

            // Do not place zero in the leading position.
            if (chosen == 0 && digits[i] == '0') continue;

            // Skip duplicate digits at the same recursion depth.
            if (i > 0 && digits[i] == digits[i - 1] &&
                !used[i - 1]) {
                continue;
            }

            used[i] = true;
            long long nextValue = value * 10 + (digits[i] - '0');

            if (buildPermutations(digits, used, nextValue,
                                  chosen + 1, targetLength)) {
                return true;
            }

            used[i] = false;
        }

        return false;
    }

public:
    // ---------------------------------------------------------------
    // Approach 1: Sort the digits of n and compare with each power of 2.
    // Time: O(log n * log n) for sorting digits + 31 digit sorts.
    // Space: O(log n).
    // ---------------------------------------------------------------
    bool reorderedPowerOf2SortDigits(int n) {
        string target = sortedDigits(n);

        for (int power = 1; power > 0 && power <= 1'000'000'000; power *= 2) {
            if (sortedDigits(power) == target) {
                return true;
            }
        }

        // The loop stops before int overflow; 2^30 is checked.
        return false;
    }

    // ---------------------------------------------------------------
    // Approach 2: Digit-frequency arrays.
    // Compare digit counts instead of sorting strings.
    // Time: O(log n * 31), effectively O(1) under the constraints.
    // Space: O(1).
    // ---------------------------------------------------------------
    bool reorderedPowerOf2DigitCount(int n) {
        auto target = digitCount(n);

        for (int power = 1; power <= 1'000'000'000; power *= 2) {
            if (digitCount(power) == target) {
                return true;
            }
        }

        return false;
    }

    // ---------------------------------------------------------------
    // Approach 3: Precompute signatures for all powers of two.
    // Signature is the sorted digit string.
    // Time per query: O(log n log log n) in the general expression;
    // practically O(1) because there are only 31 powers of two.
    // Space: O(1) fixed set of signatures.
    // ---------------------------------------------------------------
    bool reorderedPowerOf2PrecomputedSet(int n) {
        static const unordered_set<string> signatures = [] {
            unordered_set<string> set;
            for (int power = 1; power <= 1'000'000'000; power *= 2) {
                string s = to_string(power);
                sort(s.begin(), s.end());
                set.insert(s);
            }
            return set;
        }();

        string target = to_string(n);
        sort(target.begin(), target.end());
        return signatures.count(target) > 0;
    }

    // ---------------------------------------------------------------
    // Approach 4: Generate digit permutations.
    // Exponential: up to d! permutations, where d is digit count.
    // Duplicate digits are skipped; leading zero is forbidden.
    // Useful for learning, not recommended.
    // ---------------------------------------------------------------
    bool reorderedPowerOf2Permutation(int n) {
        string digits = to_string(n);
        sort(digits.begin(), digits.end());

        vector<bool> used(digits.size(), false);
        return buildPermutations(digits, used, 0, 0, (int)digits.size());
    }

    // ---------------------------------------------------------------
    // Approach 5: Digit-count signature encoded as a string.
    // Build a frequency signature for n, then compare with signatures
    // for powers of two. This is another O(1)-bounded approach.
    // ---------------------------------------------------------------
    bool reorderedPowerOf2FrequencySignature(int n) {
        auto signature = [&](int x) {
            array<int, 10> freq{};
            while (x > 0) {
                ++freq[x % 10];
                x /= 10;
            }

            string key;
            for (int count : freq) {
                key += to_string(count);
                key += '#';
            }
            return key;
        };

        string target = signature(n);
        for (int power = 1; power <= 1'000'000'000; power *= 2) {
            if (signature(power) == target) return true;
        }

        return false;
    }

    // Required LeetCode method. Default: simple digit-count comparison.
    bool reorderedPowerOf2(int n) {
        return reorderedPowerOf2DigitCount(n);
    }
};

/*
Examples:
n = 1   -> true  (1 is a power of 2)
n = 10  -> false (digits 1 and 0 cannot form a power of 2)
n = 46  -> true  (reorder to 64)
n = 24  -> false

Core insight:
Two numbers can be rearrangements of each other exactly when their digit
frequencies are identical. Compare n's digit signature with every power of 2.
*/


/****************************************************** C++ **************************************************************/
//Approach-1 (Using sorting)
//T.C : O(dlogd), d = number of digits
//S.C : O(d)
class Solution {
public:
    string getSortedStr(int n) {
        string s = to_string(n);
        sort(begin(s), end(s));
        return s;
    }

    bool reorderedPowerOf2(int n) {
        string s = getSortedStr(n);

        //check all 2 powers and see if it matches with s
        //2^29
        for(int p = 0; p <= 29; p++) {
            if(s == getSortedStr(1 << p)) {
                return true;
            }
        }

        return false;
    }
};



//Approach-2 (Using preprocessing and storing in a set)
//T.C : O(dlogd), d = number of digits
//S.C : O(d)
class Solution {
public:
    unordered_set<string> st;
    void buildSet() {
        //2^p from p = 0 to 29
        //convert to string
        //sort it
        //store it in st
        for(int p = 0; p <= 29; p++) {
            string s = to_string(1 << p);
            sort(begin(s), end(s));
            st.insert(s);  
        }
    }

    bool reorderedPowerOf2(int n) {
        if(st.empty()) {
            buildSet(); //call only once (static)
        }

        string s = to_string(n);
        sort(begin(s), end(s));

        return st.count(s);
    }
};


//Approach-3 (count and store digits in a vector)
//T.C : O(d), d = number of digits
//S.C : O(1)
class Solution {
public:
    vector<int> getVectorCountFormat(int n) {
        vector<int> vec(10, 0);

        //256
        //256/10 = 25
        while(n) {
            vec[n%10]++;
            n /= 10;
        }

        return vec;
    }

    bool reorderedPowerOf2(int n) {
        vector<int> input = getVectorCountFormat(n);

        for(int p = 0; p <= 29; p++) {
            if(input == getVectorCountFormat(1 << p)) {
                return true;
            }
        }

        return false;
    }
};


//Approach-4 (count and store digits in a number)
//T.C : O(d), d = number of digits
//S.C : O(1)
class Solution {
public:
    int getVectorCountFormat(int n) {
        int num = 0;

        //256
        //256/10 = 25
        while(n) {
            num += pow(10, n%10);
            n /= 10;
        }

        return num;
    }

    bool reorderedPowerOf2(int n) {
        int input = getVectorCountFormat(n);

        for(int p = 0; p <= 29; p++) {
            if(input == getVectorCountFormat(1 << p)) {
                return true;
            }
        }

        return false;
    }
};

