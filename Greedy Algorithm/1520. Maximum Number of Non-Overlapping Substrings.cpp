class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> start(26, -1);
        vector<int> end(26, -1);
        vector<bool> isValid(26, true);
        vector<string> res ;
        

        for(int i=0; i<n; i++) {
            int x = s[i] - 'a';
            if(start[x] == -1) {
                start[x] = i;
            }

            end[x] = i ;
        }

        // checking for all characters
        for(int c=0; c < 26; c++) {

            if(start[c] == -1 ) continue;

            for(int i=start[c]; i<= end[c]; i++) {

                if(start[s[i] - 'a'] < start[c]) {
                    isValid[c] =  false;
                    break;
                }
                
                end[c] = max(end[c], end[s[i]-'a']);
            }
        }

        int lastTakenStartIdx = INT_MAX  ;
        for(int i=n-1; i>=0; i--) {
            int c = s[i] - 'a';

            if(!isValid[c]) continue;

            if(i == start[c] && end[c] < lastTakenStartIdx) {
                lastTakenStartIdx = i ;
                res.push_back(s.substr(i, end[c]-i+1));
            }
        }
        return res;
    }
};