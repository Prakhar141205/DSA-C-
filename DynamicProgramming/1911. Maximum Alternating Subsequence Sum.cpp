// pure recursion

typedef long long ll;
class Solution {
public:
    ll solve(vector<int>& nums, int idx, bool flag, int n){
        if(idx == n) return  0;


        ll skip = solve(nums, idx+1, flag, n); // flag same because in skip index remains same 

        ll val = nums[idx];

        if(!flag) val = -1 * val;

        long long take = solve(nums, idx+1, !flag, n) + val ;

        return max(take, skip);

    }
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        int idx=0;
        bool flag = true; // 0th index is even
        return solve(nums, idx, flag, n);
        
    }
};


// using Memoization

typedef long long ll;
class Solution {
public:
    ll solve(vector<int>& nums, int idx, bool flag, int n, ll dp[][2]){
        if(idx == n) return  0;

        if(dp[idx][flag] != -1) return dp[idx][flag];

        ll skip = solve(nums, idx+1, flag, n, dp); // flag same because in skip index remains same 

        ll val = nums[idx];

        if(!flag) val = -1 * val;

        long long take = solve(nums, idx+1, !flag, n, dp) + val ;

        return dp[idx][flag] = max(take, skip);

    }
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        int idx=0;
        bool flag = true; // 0th index is even

        ll dp[n+1][2];
        memset(dp, -1, sizeof(dp));
        return solve(nums, idx, flag, n, dp);
        
    }
};


// using tabulation

typedef long long ll;
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        ll dp[100001][2] = {0};
        
        for(int i=1; i<n+1; i++){

            dp[i][0] = max(dp[i-1][1] - nums[i-1], dp[i-1][0]); // dp[i][even] = max(dp[i-1][odd] - nums[i], dp[i-1][even])

            dp[i][1] = max(dp[i-1][0] + nums[i-1], dp[i-1][1]);  // dp[i][odd] = max(dp[i-1][even] - nums[i], dp[i-1][odd])
        }
        return max(dp[n][0], dp[n][1]);
    }
};