class Solution {
public:
    int n ;
    int t[100001][2] ;
    int solve(string& s, int i, char prev) {
        if(i >= n) return 0;

        int flip = INT_MAX, not_flip = INT_MAX ;
        // i ==> current index
        // prev ==> prevChar
        if(t[i][prev - '0'] != -1) return t[i][prev - '0'] ;

        if(s[i] == '1') {
            if(prev == '0') {
                 flip = 1 + solve(s, i+1, '0');
                 not_flip = solve(s, i+1, '1');

                // ans = min(flip, not_flip) ;
            }else {
                not_flip = solve(s, i+1, '1') ;
            }
        }else {
            if(prev == '0') {
                 flip = 1 + solve(s, i+1, '1');
                 not_flip = solve(s, i+1, '0');

                // ans = min(flip, not_flip) ;
            }else {
                flip = 1 + solve(s, i+1, '1') ;
            }
        }

        return t[i][prev - '0'] = min(flip, not_flip) ;
    } 
    int minFlipsMonoIncr(string s) {
        n = s.length();
        memset(t, -1, sizeof(t));
        return solve(s, 0, '0');
        
    }
};

// Bottom Up

class Solution {
public:
    int n ;
    int minFlipsMonoIncr(string s) {
        n = s.length();

        int flip = 0;
        int onesCnt = 0;

        for(int i=0; i<n; i++) {

            if(s[i] == '1') {
                onesCnt++;
            }else {
                flip = min(flip+1, onesCnt);

            }
        }
        return flip ;
    }
};