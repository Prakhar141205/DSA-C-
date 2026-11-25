/*
    Problem: Count and Say
    LeetCode: https://leetcode.com/problems/count-and-say/

    Approach: Simple Recursion

    T.C : O(2^n) (Upper-bound estimate)
    S.C : O(2^n) (Upper-bound estimate)
*/

class Solution {
public:
    string countAndSay(int n) {

        // Base case:
        // The first term of the Count and Say sequence is "1".
        if(n == 1)
            return "1";

        // Recursive call:
        // Get the previous term of the sequence.
        // For example, if n = 4, first calculate countAndSay(3).
        string say = countAndSay(n-1);

        string result = "";

        // Traverse the previous term and count consecutive characters.
        // T.C : O(m), where m = say.length().
        for(int i = 0; i < say.length(); i++) {

            // Initially, the current character appears once.
            int count = 1;

            // Store the current character.
            char ch = say[i];

            // Count consecutive occurrences of the current character.
            // Move i forward as long as the next character is the same.
            while(i < say.length()-1 && say[i] == say[i+1]) {
                count++;
                i++;
            }

            // Append the frequency followed by the character.
            // Example:
            // "111" -> "31"
            // "21"  -> "1211"
            result += to_string(count) + string(1, say[i]);
        }

        // Return the newly generated term.
        return result;
    }
};