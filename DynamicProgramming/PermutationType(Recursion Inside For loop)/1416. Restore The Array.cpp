class Solution {
public:
    const int mod = 1e9 + 7 ;
    int n;
    int t[100001] ;
    int solve(int st, string& s, int& k ) {

        if(st >= n) return 1;
        if(s[st] == '0') return 0;
        if(t[st] != -1) return t[st] ;

        long ans = 0;
        long long num = 0;
        for(int i=st; i<n; i++) { // i == end
            num = num * 10 + (s[i] - '0') ;

            if(num > k) break;
            
            ans = ( ans%mod + solve(i+1, s, k)) % mod ;
        }

        return t[st] = ans%mod ;
    }
    int numberOfArrays(string s, int k) {
        n = s.length();
        memset(t, -1, sizeof(t));
        return solve(0, s, k) ;
        
    }
};