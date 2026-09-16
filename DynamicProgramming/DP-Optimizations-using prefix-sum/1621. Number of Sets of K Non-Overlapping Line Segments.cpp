class Solution {
public:
    const int mod = 1e9+7;
    
    int numberOfSets(int n, int K) {
        vector<vector<int>> t(K+1, vector<int> (n+1, 0)) ;

        for(int i=0; i< n; i++) {
            t[0][i] = 1 ;
        }

        for(int k=1; k<=K; k++) {
            vector<int> prevRowSum(n+1, 0);
            for(int x=n-1; x >= 0; x--) {
                prevRowSum[x] = (prevRowSum[x+1] + t[k-1][x])%mod ;
            }
            for(int i=n-1; i>=0; i--) {
                
                int take  = prevRowSum[i+1];
                int skip = t[k][i+1] % mod;
                t[k][i] = (take+skip) % mod;
            }
        }
        return t[K][0]%mod;
    }
};