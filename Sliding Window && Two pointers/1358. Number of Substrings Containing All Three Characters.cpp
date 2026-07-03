class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length();

        int l=0, r=0;

        int cnt_a=0, cnt_b=0, cnt_c=0;
        int ans=0;

        while(r < n) {
            if(s[r] == 'a') cnt_a++;
            else if(s[r] == 'b') cnt_b++;
            else cnt_c++;

            while(cnt_a && cnt_b && cnt_c) {
                ans += (n-r) ;
                    if(s[l] == 'a') cnt_a--;
                    else if(s[l] == 'b') cnt_b--;
                    else cnt_c--;
                l++;
            }

            r++;

        }
        return ans;
    }
};