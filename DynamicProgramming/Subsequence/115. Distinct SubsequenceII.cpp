class Solution {
public: 
    int dp[1001][1001] ;

    int solve(string& s, string& t, int m, int n) {

        if(n == 0) return 1;
        if(m == 0) return  0;

        if(dp[m][n] != -1 ) return dp[m][n] ;

        int match = 0;
        int notmatch = 0;
        if(s[m-1] == t[n-1]) {
            match = solve(s, t, m-1, n-1) + solve(s, t, m-1, n);
        }else {
            notmatch = solve(s, t, m-1, n) ;
        }

        return  dp[m][n] = match + notmatch;
    }
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        memset(dp, -1, sizeof(dp));

        return solve(s, t, m, n) ;
    }
};

// class Solution {
// public: 
//     typedef unsigned long long ll ;
//     int numDistinct(string s, string t) {
//         int m = s.length();
//         int n = t.length();

//         vector<vector<ll>> dp(m+1, vector<ll> (n+1, 0));

//         // Base Case 1
//         // if(n == 0) return 1
//         // dp[m][0] = 1
//         for(int i=0; i<=m; i++) {
//             dp[i][0] = 1;
//         }

//         // Base Case 2
//         // if(m == 0) return 0
//         // dp[0][n] = 1
//         for(int i=0; i<=n; i++) {
//             dp[0][i] = 0;
//         }


//         for(int i=1; i<=m; i++) {

//             for(int j=1; j<=n; j++) {

//                 if(s[i-1] == t[j-1]) {
//                     dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
//                 }else {
//                     dp[i][j] = dp[i-1][j] ;
//                 }
//             }
//         }

//         return (int)dp[m][n] ;
//     }
// };

class Solution {
public:
    int numDistinct(string s, string t) {
        int n=s.size(),m=t.size();
        vector<vector<double>>dp(n+1,vector<double>(m+1,0));
        for(int i=0;i<n+1;i++){
            dp[i][0]=1;
        }
        for(int i=1;i<n+1;i++){
            for(int j=1;j<m+1;j++){
                if(s[i-1]==t[j-1]){
                    dp[i][j]=dp[i-1][j]+dp[i-1][j-1];
                }else{
                    dp[i][j]=dp[i-1][j];
                }
            }
        }
        return (int)dp[n][m];

    }
};
