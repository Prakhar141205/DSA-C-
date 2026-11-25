/*
    Problem: Integer to Roman
    LeetCode: https://leetcode.com/problems/integer-to-roman/

    Approach: Greedy

    T.C : O(1) - Fixed 13 Roman numeral values.
    S.C : O(1) - Excluding the output string.
*/

class Solution {
public:
    // Store Roman numeral values in descending order.
    // Include special cases like 900, 400, 90, 40, 9 and 4
    // to handle subtractive notation.
    vector<int> val{
        1000, 900, 500, 400, 100, 90, 50,
        40, 10, 9, 5, 4, 1
    };

    // Corresponding Roman symbols for the above values.
    vector<string> sym{
        "M", "CM", "D", "CD", "C", "XC", "L",
        "XL", "X", "IX", "V", "IV", "I"
    };

    string intToRoman(int num) {

        string result = "";
        int i = 0;

        // Process the number using greedy selection.
        // Always choose the largest possible Roman numeral value.
        while(num > 0) {

            // Keep using the current Roman numeral
            // as long as num is greater than or equal to its value.
            while(num >= val[i]) {

                // Subtract the selected Roman numeral value.
                num -= val[i];

                // Append its corresponding Roman symbol.
                result += sym[i];
            }

            // Move to the next smaller Roman numeral value.
            i++;
        }

        // Return the final Roman numeral representation.
        return result;
    }
};