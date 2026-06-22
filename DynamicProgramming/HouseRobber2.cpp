// recursion + Memmo

class Solution {
public:
    int solve(vector<int> nums, int st, int end, vector<int>& dp){
        if(st > end) return 0;

        if(dp[st] != -1) return dp[st];

        int take = solve(nums, st+2, end, dp) + nums[st];
        int skip = solve(nums, st+1, end, dp);

        return dp[st] = max(take, skip); 
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]); 
        vector<int> dp1(n+1, -1);
        vector<int> dp2(n+1, -1);
        return max(solve(nums, 0, n-2, dp1), solve(nums, 1, n-1, dp2));
        
    }
};

// using tabulation

class Solution {
public:
    
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> dp(n+1, -1);

        dp[0] = 0;

        // robbed first house => 0th house
        for(int i=1; i<= n-1; i++){
            int take = nums[i-1] + ((i-2) >= 0 ? dp[i-2] : 0) ;
            int skip = dp[i-1];
            dp[i]  = max(take, skip);
        }
        int result1 = dp[n-1];
        // skipped first house => skipped 0th house

        dp.clear();
        // dp.assign(n+1, 0);
        dp[0] = 0;
        dp[1] = 0;
        for(int i=2; i<= n; i++){
            int take = nums[i-1] + ((i-2) >= 0 ? dp[i-2] : 0) ;
            int skip = dp[i-1];
            dp[i]  = max(take, skip);
        }
        int result2 = dp[n];

        return max(result1, result2);
        
    }
};