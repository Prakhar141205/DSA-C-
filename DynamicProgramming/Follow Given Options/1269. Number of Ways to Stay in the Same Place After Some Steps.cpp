class Solution {
public:
    int ARRLEN;
    int STEPS;
    int t[501][501] ;
    const int mod = 1e9 + 7 ;
    int solve(int currSteps, int i) {
        if(i < 0 || i >= ARRLEN ) return 0; 
        if(currSteps > STEPS) return 0;
        if(currSteps == STEPS) return i == 0;
        if(t[currSteps][i] != -1) return t[currSteps][i]%mod ;
        int res = 0;
        res = (res + solve(currSteps+1, i-1))%mod;
        res = (res + solve(currSteps+1, i+1))%mod;
        res = (res + solve(currSteps+1, i))%mod;

        return t[currSteps][i] = res %mod;
    }
    int numWays(int steps, int arrLen) {

        ARRLEN = min(arrLen, steps);
        STEPS = steps;
        memset(t, -1, sizeof(t));
        return solve(0, 0)%mod;
    }
};