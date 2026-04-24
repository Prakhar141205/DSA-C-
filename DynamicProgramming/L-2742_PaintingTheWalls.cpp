// Tabulation using DP =? variation of 0-1 knapsack Problem

class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        // 0/1 knapsack problem 3.tabulation/bottom up 
        int n = cost.size();
        vector<int>dp(n+1, 1e9);
        dp[0] = 0;
        for(int i = 0; i < n; i++){
            for(int j = n-1; j >= 0; j--){
                int newcover = min(n, j + time[i] + 1);
                dp[newcover] = min(dp[newcover], dp[j] + cost[i]);
            }
        }
        return dp[n];
    }
};


// DP Memoization

class Solution {
public:
    int n;
    int helper(vector<int>& cost, vector<int>& time, int idx, int walls, vector<vector<int>> &dp){
        if(walls <= 0) return 0;
        if(idx >= n) return 1e9;
        

        if(dp[idx][walls] != -1){
            return dp[idx][walls];
        }
        
        int incCost = cost[idx] + helper(cost, time, idx+1, walls-1-time[idx], dp);
        int notIncCost = helper(cost, time, idx+1, walls, dp);

        return dp[idx][walls] = min(incCost, notIncCost);
    }
    int paintWalls(vector<int>& cost, vector<int>& time) {
        n = cost.size();
        vector<vector<int>> dp(n+1, vector<int> (n+1, -1));

        return helper(cost, time, 0, n,  dp);
        
    }
};