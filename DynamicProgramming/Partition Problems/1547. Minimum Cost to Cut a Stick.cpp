class Solution {
public:
    int t;
    int dp[103][103] ;

    int solve(vector<int>& cuts, int l, int r) {
        if(r-l <= 1) return 0;
        if(dp[l][r] != -1) return dp[l][r];
        int result = INT_MAX;

        for(int i=l+1; i<= r-1; i++) {

            // cost = length + ans of 0, index + ans of index to r
            int cost =  ( cuts[r] - cuts[l] ) + solve(cuts, l, i) + solve(cuts, i, r);

            result = min(cost, result);
        }

        return dp[l][r] = result;
    }
    int minCost(int n, vector<int>& cuts) {
        sort(begin(cuts), end(cuts));


        cuts.insert(begin(cuts), 0);
        cuts.push_back(n);
        t = cuts.size();

        memset(dp, -1, sizeof(dp));
        return solve(cuts, 0, t-1);
    }
};