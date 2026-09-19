class Solution {
public:
    int dp[1001][1001];

    int solve(int i, int j, string& s, string& t) {
        if(i < 0) {
            int ans = 0;
            while(j >= 0)  {
                ans += t[j--] ;
            }
            return ans ;
        }

        if( j < 0) {
            int ans = 0;
            while(i >= 0) {
                ans += s[i--] ;
            }
            return ans;
        }

        if(dp[i][j] != -1) return dp[i][j] ;

        if(s[i] != t[j]) {

            return dp[i][j] = min(s[i] + solve(i-1, j, s, t), t[j] + solve(i, j-1, s, t));
        }

        return dp[i][j] = solve(i-1, j-1, s, t);
    }
    int minimumDeleteSum(string s, string t) {
        int m = s.length();
        int n = t.length();
        memset(dp, -1, sizeof(dp)) ;
        return solve(m-1, n-1, s, t) ;
    }
};