// Approach-1 (Using Map and doing as asked in Problem)
// T.C : O(n)
// S.C : O(1) - At most 8 keys in the unordered_map

class Solution {
public:
    int minimumPushes(string word) {

        // If word length is <= 8, each character can be
        // assigned to a different key and requires only 1 push.
        // T.C : O(1)
        if(word.length() <= 8) {
            return word.length();
        }

        int count = 0;

        // Store the frequency of characters assigned to each key.
        // Keys range from 2 to 9.
        unordered_map<int, int> mp;

        int assign = 2;

        // Assign characters to keys in a round-robin manner.
        // Each key can accommodate 1 character at each push level.
        // T.C : O(n) average
        for(char &ch : word) {

            // After assigning all 8 keys (2 to 9),
            // start assigning characters from key 2 again.
            if(assign > 9) {
                assign = 2;
            }

            // Increase the number of characters assigned to this key.
            // T.C : O(1) average
            mp[assign]++;

            // The current character requires as many pushes
            // as the number of characters assigned to this key.
            // Add its push count to the answer.
            count += mp[assign];

            // Move to the next key.
            assign++;
        }

        return count;
    }
};

// Approach-2 (Simplifying Approach-1)
// T.C : O(n) + O(26 log 26) + O(26)
//     = O(n) + O(26 log 26)
//     = O(n), since 26 is constant.
// S.C : O(1)

class Solution {
public:
    int minimumPushes(string word) {

        // Frequency array to store the frequency of each character.
        // Since all characters are distinct (as mentioned in the problem),
        // each character will have frequency either 0 or 1.
        // T.C : O(26) = O(1)
        vector<int> mp(26, 0);

        // Mark the presence of every character.
        // T.C : O(n)
        for(char &ch : word) {
            mp[ch - 'a'] = 1;
        }

        // Sort frequencies in descending order.
        // Characters with higher frequencies should get keys
        // requiring fewer pushes.
        // T.C : O(26 log 26) = O(1)
        sort(begin(mp), end(mp), greater<int>());

        int ans = 0;

        // Calculate the minimum number of pushes.
        // First 8 characters require 1 push.
        // Next 8 characters require 2 pushes.
        // Next 8 characters require 3 pushes, and so on.
        // T.C : O(26) = O(1)
        for(int i = 0; i < 26; i++) {

            // (i / 8) + 1 determines the number of pushes required.
            // Multiply it by the frequency of the character.
            ans += mp[i] * ((i / 8) + 1);
        }

        return ans;
    }
};