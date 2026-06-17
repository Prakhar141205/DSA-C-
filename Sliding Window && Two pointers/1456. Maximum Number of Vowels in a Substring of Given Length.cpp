// without queue
class Solution {
public:
    bool isVowel(char c){
        if(c == 'a' ||
        c == 'e' || 
        c == 'i' || 
        c == 'o' || 
        c == 'u') return true;

        else return false;
    }
    int maxVowels(string s, int k) {
        int n = s.length();
        int l=0, r=0; 
        int maxNumberVowels = 0;
        // unordered_map<char, int> mp;
        // queue<char> q; 
        int cnt=0;
        while(r < n){
            if(isVowel(s[r]))
                // mp[s[r]]++;
                // q.push(s[r]);
                cnt++;

            if(r - l + 1 == k){
                // int currentWindowVowels = q.size();
                maxNumberVowels = max(maxNumberVowels, cnt);

                if(isVowel(s[l])){
                    // q.pop();
                    cnt--;
                }

                l++;
            }

            r++;
        }
        return maxNumberVowels;
    }
};

// with queue
class Solution {
public:
    bool isVowel(char c){
        if(c == 'a' ||
        c == 'e' || 
        c == 'i' || 
        c == 'o' || 
        c == 'u') return true;

        else return false;
    }
    int maxVowels(string s, int k) {
        int n = s.length();
        int l=0, r=0; 
        int maxNumberVowels = 0;
        // unordered_map<char, int> mp;
        queue<char> q; 
        while(r < n){
            if(isVowel(s[r]))
                // mp[s[r]]++;
                q.push(s[r]);

            if(r - l + 1 == k){
                int currentWindowVowels = q.size();
                maxNumberVowels = max(maxNumberVowels, currentWindowVowels);

                if(isVowel(s[l])){
                    q.pop();
                }

                l++;
            }

            r++;
        }
        return maxNumberVowels;
    }
};

class Solution {
public:
    int maxVowels(string s, int k) {
        auto isVowel = [](char c) {
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        };
        int cnt = count_if(s.begin(), s.begin() + k, isVowel);
        int ans = cnt;
        for (int i = k; i < s.size(); ++i) {
            cnt += isVowel(s[i]) - isVowel(s[i - k]);
            ans = max(ans, cnt);
        }
        return ans;
    }
};