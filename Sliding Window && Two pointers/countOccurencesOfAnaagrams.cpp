
class Solution {
  public:
    bool allZero(vector<int> counter){
        
        for(int x : counter){
            if (x != 0) return false;
        }
        return true;
    }
    int search(string &pat, string &txt) {
        int n = txt.length(); 
        int l=0, r=0;
        vector<int> counter(26, 0);
        
        // store the freq of characterr of pattern
        for(char& c: pat) counter[c-'a']++;
        
        int k = pat.length();
        int result = 0;
        // sliding window approach
        while(r < n){
            char c = txt[r];
            
            counter[c-'a']--;
            
            if(r-l+1 == k){
                if(allZero(counter)){
                    result++;
                }
                // window se bahar jane se pahle 
                // jo character window se bahar jayega uski freq increase krni hogi
                counter[txt[l] - 'a']++;
                l++;
            }
            r++;
            
        }
        return result;
    }
};