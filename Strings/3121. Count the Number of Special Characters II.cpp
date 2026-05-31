#include <vector>
#include <string>
class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<int> lastLower(26, -1);
        vector<int> firstUpper(26, -1);

        for(int i = 0; i < word.size(); i++) {
            char ch = word[i];

            if(ch >= 'a' && ch <= 'z') {
                lastLower[ch - 'a'] = i;
            }
            else {
                if(firstUpper[ch - 'A'] == -1) {
                    firstUpper[ch - 'A'] = i;
                }
            }
        }

        int count = 0;

        for(int i = 0; i < 26; i++) {
            if(lastLower[i] != -1 &&
               firstUpper[i] != -1 &&
               lastLower[i] < firstUpper[i]) {
                count++;
            }
        }

        return count;
    }
};

class Solution {
public:
    int numberOfSpecialChars(string word) {
        vector<bool> lowerSeen(26, false);
        vector<bool> upperSeen(26, false);
        vector<bool> invalid(26, 0);

        int n = word.length();

        for(int i=0; i<n; i++){
            char ch = word[i];
            if(ch >= 'A' && ch <= 'Z') upperSeen[ch - 'A'] = true;
            else {
                lowerSeen[ch - 'a'] = true;
                if(upperSeen[ch - 'a']) invalid[ch - 'a'] = true;
               
            }
        }
        int cnt=0;
        for(int i=0; i<26; i++){
            if(lowerSeen[i] && upperSeen[i] && !invalid[i]) cnt++;
        }
        return cnt;
    }
};

class Solution {
public:
    int numberOfSpecialChars(string word) {
        static int mp[125] {};
        memset(mp, 0, sizeof(mp));
        for(int i = 0, n = word.size(); i < n; i++)
            if(islower(word[i]) || !mp[word[i]])
                mp[word[i]] = i + 1;
        int ans = 0;
        for(char ch = 'a'; ch <= 'z'; ch++) {
            if(mp[ch] && mp[toupper(ch)] > mp[ch]) ans++;
        }
        return ans;
    }
};