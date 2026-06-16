// Sliding Window approach

class Solution {
public:
    string minWindow(string s, string t) {

        int minLen = 1e9, startIndex=0;

        int n = s.length(), m = t.length();
        if(m > n ) return "";

        int l=0, r=0;
        unordered_map<char, int> mp; // char , freq of t string

        // stores the freq of char of string t
        for(char& c : t) mp[c]++;

        int cntRequired = m;

        while(r < n){
            char c = s[r];
            if(mp[c] > 0){
                cntRequired--;
            }

            mp[c]--;
            // start shrinking the window
            while(cntRequired == 0){
                int currWindowLen = r-l+1;

                if(currWindowLen  < minLen){
                    minLen = currWindowLen;
                    startIndex = l;
                }

                mp[s[l]]++;

                if(mp[s[l]] > 0){
                    cntRequired++;
                }
                l++;
            }
            r++;
        }
        
        return minLen == 1e9 ? "" :s.substr(startIndex, minLen);       
    }
};

// TC O(N^2)

class Solution {
public:
    string minWindow(string s, string t) {
        int minLen = 1e9, startIndex=-1;
        int n = s.length(), m = t.length();

        for(int i=0; i<n; i++){
            int hash[256] = {0};
            int cnt=0;

            for(char x : t) hash[x]++;

            for(int j=i; j<n; j++){
                if(hash[s[j]] > 0){
                    cnt += 1;
                    
                }
                hash[s[j]]--;

                if(cnt == m){
                    if(j-i+1 < minLen){
                    minLen = j-i+1;
                    startIndex = i;
                    break;
                    }
                }
            }
        } 
        cout << startIndex;
        return startIndex == -1 ? "" :s.substr(startIndex, minLen);       
    }
};

