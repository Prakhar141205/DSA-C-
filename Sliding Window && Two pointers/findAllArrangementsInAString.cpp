class Solution {
public:
    bool allZero(vector<int> counter){

        for(int& x: counter) if(x != 0) return false;

        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        int l=0, r=0;
        vector<int> ans;
        
        int n = s.length();
        vector<int> counter(26, 0);
        // store the freq of p string

        for(char& c : p) counter[c-'a']++;
        int pLen = p.length();

        while(r < n){
            // agar char window mein add hoga to uski freq decrease krni hai
            counter[s[r]-'a']--;

            if(r - l + 1 == pLen){

                if(allZero(counter)){
                    ans.push_back(l);
                }

                counter[s[l]-'a']++; // jo character window se bahar gya hai uski freq plus krni
                l++; // reduce the window size
            }

            r++;
        }
        return ans;
    }
};