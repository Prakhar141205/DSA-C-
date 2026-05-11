// using Memoization
class Solution {
public:
    
    int find(int ind,vector<int>&nums,int tar,vector<int>&dp)
    {
        if(ind==nums.size()-1)
        {
            return 0;
        }
        
        if(dp[ind]!=-1)
            return dp[ind];
        
        int ans=INT_MIN;
        
        for(int i=ind+1;i<nums.size();i++)
        {
            if(abs(nums[i]-nums[ind])<=tar)
            {
                ans=max(ans,1+find(i,nums,tar,dp));
            }
        }
        return dp[ind]=ans;
    }
    int maximumJumps(vector<int>& nums, int tar)
    {
        vector<int>dp(nums.size(),-1);
        int ans=find(0,nums,tar,dp);
       if(ans>0)
           return ans;
        else
            return -1;
    }
};


// using tabulation
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> dp(n, -1);
        dp[0] = 0;

        for (int i = 0; i < n - 1; i++) {
            if (nums[i] != -1) {
                for (int j = i + 1; j < n; j++) {
                    if (abs(nums[i] - nums[j]) <= target && dp[i] != -1) {
                        dp[j] = max(dp[j], dp[i] + 1);
                    }
                }
            } 
        }

        return dp[n - 1];
    }
};