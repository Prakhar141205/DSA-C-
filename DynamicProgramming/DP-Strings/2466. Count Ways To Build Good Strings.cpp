class Solution {
public:
    int LOW, HIGH, ZERO, ONE, mod = 1e9+7;
    int t[100001];
    int solve(int n) {
        if(n > HIGH) return 0;
        if(t[n] != -1) return t[n];
        bool isValid = false;

        if(n >= LOW && n <= HIGH)  {
            isValid = true;
        }


        int append1 = solve(n + ONE) % mod;
        int append0 = solve(n + ZERO) % mod;

        return t[n] = (isValid + append1 + append0) % mod;
    }
    int countGoodStrings(int low, int high, int zero, int one) {
        LOW = low;
        HIGH = high;
        ZERO = zero;
        ONE = one;
        memset(t, -1, sizeof(t));   
        return solve(0) % mod;
    }
};