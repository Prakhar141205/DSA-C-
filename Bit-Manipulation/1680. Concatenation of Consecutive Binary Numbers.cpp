class Solution {
public:
    int mod = 1e9+7;
    typedef long long ll;

    int concatenatedBinary(int n) {
        ll result = 0;
        
        
        for(int i=1; i<=n; i++) {
            int bits = log2(i) + 1;

            result = (((result << bits) % mod ) + i)%mod  ;
        }

        return result; 
    }
};