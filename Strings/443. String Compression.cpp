// Approach: Two Pointers
// T.C : O(n)
// S.C : O(1)

class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();

        // i     : Pointer to traverse the original characters.
        // index : Pointer to write the compressed characters.
        int i = 0;
        int index = 0;

        // Traverse the entire character array.
        // T.C : O(n)
        while(i < n) {

            // Store the current character.
            char curr = chars[i];

            int count = 0;

            // Count consecutive occurrences of the current character.
            // Move i forward until a different character is found.
            // T.C : O(n) overall because every character is visited once.
            while(i < n && chars[i] == curr) {
                i++;
                count++;
            }

            // Write the current character at the write pointer.
            // T.C : O(1)
            chars[index] = curr;
            index++;

            // If the character occurs more than once,
            // append its frequency after the character.
            if(count > 1) {

                // Convert the integer frequency into a string.
                // Example: 12 -> "12"
                // T.C : O(log count)
                string count_str = to_string(count);

                // Write every digit of the frequency into chars.
                // T.C : O(log count)
                for(char &ch : count_str) {
                    chars[index] = ch;
                    index++;
                }
            }
        }

        // index represents the length of the compressed array.
        // Characters beyond index are irrelevant.
        return indclass Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int k = 0;
        int i=0;
        while(i < n) {
            char curr_char = chars[i];
            int cnt = 0;

            while(i < n && chars[i] == curr_char) {
                cnt++;
                i++;
            }

            chars[k] = curr_char;
            k++;
            if(cnt > 1) {
                string curr = to_string(cnt);
                for(char c : curr) {
                    chars[k] = c;
                    k++;
                   
                }
            }
        }

        return k;
    }
};ex;
    }
};