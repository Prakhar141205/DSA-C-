// using memoization
class Solution {
public:
    int solve(vector<int>& nums, int i, int n, vector<int>& dp){
        if(i > n) return 0;

        if(dp[i] != -1) return dp[i];

        int take = nums[i] + solve(nums, i+2, n, dp);
        int skip = solve(nums, i+1, n, dp);

        return dp[i] = max(take, skip);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        int i=0;
        vector<int> dp = vector<int>(101, -1);
        return solve(nums, i, n-1, dp);
    }
};

// using tabulation

class Solution {
public:
    
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        
        vector<int> dp = vector<int>(101, -1);

        dp[0] = 0; // we have zero house 
        dp[1] = nums[0]; // we have one house

        for(int i=2; i<=n; i++){

            int take = dp[i-2] + nums[i-1]; // dp ka 2 house nums ka 1 house hoga
            dp[i] = max(dp[i-2] + nums[i-1], dp[i-1]);
        }
        return dp[n];
    }
};

// using constant space solution
class Solution {
public:
    
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);
        
        // vector<int> dp = vector<int>(101, -1);

        // dp[0] = 0; // we have zero house 
        // dp[1] = nums[0]; // we have one house
        int prev2 = 0;
        int prev1 = nums[0];
        int result = 0;
        for(int i=2; i<=n; i++){
        
            int take = prev2 + nums[i-1]; // dp ka 2 house nums ka 1 house hoga
            int skip = prev1;
            result = max(take, skip);

            prev2 = prev1;
            prev1 = result;
        }
        return result;
    }
};