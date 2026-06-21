class Solution {
public:
    long long solv(int i, int p, bool t, bool nz, string &s, int k, vector<vector<vector<vector<long long>>>> &dp) {
        if(i== s.size()) return nz;
        if(dp[i][p][t][nz]!= -1) return dp[i][p][t][nz];
        long long ans=0;
        int lm= t?s[i]-'0': 9;
        for(int j=0; j<lm+1; j++) {
            if(!nz) {
                bool b= (t&& j == lm);
                ans+= solv(i+1,j,b, j>0, s,k,dp);
            } else if(abs(j-p)<=k) {
                bool b= (t&& j == lm);
                ans+= solv(i+1,j,b, 1, s,k,dp);
            }
        }
        return dp[i][p][t][nz]= ans;
    }

    long long cal(long long n, int k) {
        string s= to_string(n);
        vector<vector<vector<vector<long long>>>> dp(16, vector<vector<vector<long long>>>(10, vector<vector<long long>>(2, vector<long long>(2, -1))));

        return solv(0,0,1,0, s,k, dp);
    }
    long long goodIntegers(long long l, long long r, int k) {
        return cal(r,k)- cal(l-1, k);
    }
};