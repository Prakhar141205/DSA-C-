class Solution {
public:
    const int mod = 1e9+7;
    int  t[2001];

    vector<int> prev; // prev[i] last time when we saw this nth character  (1 based indexing)

    int solve(int n ) {
        if(n == 0) return 1 ;

        if(t[n] != -1) return t[n];

        int total = (2*solve(n-1)) % mod ;
        if(prev[n] != 0){
            int duplicates = solve(prev[n]-1);
            total = (total - duplicates + mod) % mod;
        }
        return t[n] = total % mod;
    }
    int distinctSubseqII(string s) {
        int n = s.length();

        memset(t, -1, sizeof(t));

        prev.assign(n+1, 0);

        vector<int> lastSeen(26, 0);

        for(int i=1; i<=n; i++) {
            int idx = s[i-1] - 'a' ;
            prev[i] = lastSeen[idx];
            lastSeen[idx] = i ; 
        }

        return (solve(n) - 1 + mod) % mod ;
        
    }
};