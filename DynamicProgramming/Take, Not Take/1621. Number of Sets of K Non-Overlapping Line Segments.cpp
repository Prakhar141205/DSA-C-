class Solution {
public:
    const int mod = 1e9+7;
    int ans = 0;
    int t[1001][1001] ;

    int solve(int n, int k, int i) {
        if(k == 0) return 1;
        if(i >= n) return 0;
        if(t[k][i] != -1) return t[k][i];
        int skip = solve(n, k, i+1) % mod;
        long long take = 0;
        for(int j=i+1; j<n; j++) {
            take = (take + solve(n, k-1, j)) % mod;
        }

       return t[k][i] = (take + skip)%mod ;
    }
    int numberOfSets(int n, int k) {
        memset(t, -1, sizeof(t));
        return solve( n,  k,  0)%mod;
    }
};

// Bottom Up
class Solution {
public:
    const int mod = 1e9+7;
    
    int numberOfSets(int n, int K) {
        vector<vector<int>> t(K+1, vector<int> (n+1, 0)) ;

        for(int i=0; i< n; i++) {
            t[0][i] = 1 ;
        }

        for(int k=1; k<=K; k++) {

            for(int i=n-1; i>=0; i--) {
                int take = 0;
                for(int j = i+1; j<n; j++) {
                    take = (take%mod + t[k-1][j]) % mod ;
                }
                int skip = t[k][i+1] % mod;
                t[k][i] = (take+skip) % mod;
            }
        }
        return t[K][0]%mod;
    }
};