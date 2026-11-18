class Solution {
public:
    int minChanges(string s) {
        int n = s.length();
        int j=0;
        int ans = 0;
        int len = 1;
        for(int i=1; i<n; i++) {

            if(s[i] != s[i-1] ) {
                if(len % 2 == 1) {
                    ans++;
                    s[i] = s[i-1];
                }
            }
            len++;
        }

        return ans;
    }
};