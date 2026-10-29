/*
LeetCode 273. Integer to English Words
C++ solutions from multiple approaches.

Copy ONE class and rename it to Solution before submitting on LeetCode.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Approach 1: Split into groups of three digits (recommended).
- Each group is in [0, 999].
- Convert each non-zero group into words.
- Add its scale: Thousand, Million, Billion.
Time: O(1) for a 32-bit integer (at most four groups).
Space: O(1), excluding the output string.
*/
class Solution1 {
    const vector<string> below20 = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen",
        "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    const vector<string> tens = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty",
        "Sixty", "Seventy", "Eighty", "Ninety"
    };
    const vector<string> scales = {"", "Thousand", "Million", "Billion"};

    string convertUnder1000(int n) {
        string out;
        if (n >= 100) {
            out += below20[n / 100] + " Hundred";
            n %= 100;
            if (n) out += " ";
        }
        if (n >= 20) {
            out += tens[n / 10];
            n %= 10;
            if (n) out += " ";
        }
        if (n > 0 && n < 20) out += below20[n];
        return out;
    }

public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";

        string result;
        int scaleIndex = 0;
        while (num > 0) {
            int group = num % 1000;
            if (group != 0) {
                string part = convertUnder1000(group);
                if (!scales[scaleIndex].empty())
                    part += " " + scales[scaleIndex];

                result = result.empty() ? part : part + " " + result;
            }
            num /= 1000;
            ++scaleIndex;
        }
        return result;
    }
};

/*
Approach 2: Recursive range-based conversion.
- Handle values below 20 and 100 directly.
- For larger values, recursively convert the leading part and remainder.
Time: O(1) for the fixed 32-bit range.
Space: O(1) recursion depth for the fixed range.
*/
class Solution2 {
    const vector<string> below20 = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen",
        "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    const vector<string> tens = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty",
        "Sixty", "Seventy", "Eighty", "Ninety"
    };

    string convert(int n) {
        if (n == 0) return "";
        if (n < 20) return below20[n];

        if (n < 100) {
            string out = tens[n / 10];
            if (n % 10) out += " " + convert(n % 10);
            return out;
        }
        if (n < 1000) {
            string out = below20[n / 100] + " Hundred";
            if (n % 100) out += " " + convert(n % 100);
            return out;
        }
        if (n < 1000000) {
            string out = convert(n / 1000) + " Thousand";
            if (n % 1000) out += " " + convert(n % 1000);
            return out;
        }
        if (n < 1000000000) {
            string out = convert(n / 1000000) + " Million";
            if (n % 1000000) out += " " + convert(n % 1000000);
            return out;
        }
        string out = convert(n / 1000000000) + " Billion";
        if (n % 1000000000) out += " " + convert(n % 1000000000);
        return out;
    }

public:
    string numberToWords(int num) {
        return num == 0 ? "Zero" : convert(num);
    }
};

/*
Approach 3: Store converted groups, reverse them, and join.
This is an alternative iterative implementation of group decomposition.
Time: O(1) for the fixed 32-bit range.
Space: O(1), with at most four groups.
*/
class Solution3 {
    const vector<string> small = {
        "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen",
        "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    const vector<string> tens = {
        "", "", "Twenty", "Thirty", "Forty", "Fifty",
        "Sixty", "Seventy", "Eighty", "Ninety"
    };
    const vector<string> place = {"", "Thousand", "Million", "Billion"};

    string under1000(int n) {
        vector<string> words;
        if (n >= 100) {
            words.push_back(small[n / 100]);
            words.push_back("Hundred");
            n %= 100;
        }
        if (n >= 20) {
            words.push_back(tens[n / 10]);
            n %= 10;
        }
        if (n > 0) words.push_back(small[n]);

        string out;
        for (const string& word : words) {
            if (!out.empty()) out += " ";
            out += word;
        }
        return out;
    }

public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";

        vector<string> groups;
        int idx = 0;
        while (num > 0) {
            int chunk = num % 1000;
            if (chunk != 0) {
                string group = under1000(chunk);
                if (!place[idx].empty()) group += " " + place[idx];
                groups.push_back(group);
            }
            num /= 1000;
            ++idx;
        }

        reverse(groups.begin(), groups.end());
        string answer;
        for (const string& group : groups) {
            if (!answer.empty()) answer += " ";
            answer += group;
        }
        return answer;
    }
};

/*
Dry run: num = 1234567
Groups from right to left:
567 -> Five Hundred Sixty Seven
234 -> Two Hundred Thirty Four Thousand
1   -> One Million

Final: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Edge cases:
0       -> Zero
100     -> One Hundred
1000    -> One Thousand
1000010 -> One Million Ten (skip the zero-thousand group)
2147483647 -> Two Billion One Hundred Forty Seven Million Four Hundred
              Eighty Three Thousand Six Hundred Forty Seven

Recommended: Solution1, because its group processing is iterative and straightforward.
*/
