class Solution {
public:
    int t[100001] ;

    int solve(int currStep, int n, vector<int>& costs) {
        if(currStep == n) return 0 ;
        if(currStep > n) return 1e9;
        
        if(t[currStep ] != -1) return t[currStep] ;

        int ans = 1e9;

        for(int j=currStep+1; j <= min(currStep+3, n); j++) {
            
            ans = min(ans, costs[j-1] + (j-currStep)*(j-currStep) + solve(j, n, costs));
        }

        return t[currStep] = ans;
    }

    int climbStairs(int n, vector<int>& costs) {
        memset(t, -1, sizeof(t)) ;

        return solve(0, n, costs);
    }
};