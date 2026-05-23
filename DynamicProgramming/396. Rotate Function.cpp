// using DP

class Solution {
public:
    
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size(), sum=0, f0 = 0;

        for(int i=0; i<n; i++ ){
            sum += nums[i];
            f0 += i * nums[i];
        } 

        vector<int> dp(n);
        dp[0] = f0;

        int maxVal = dp[0];

        for(int k=1; k<n; k++){
            dp[k] = dp[k-1] + sum - (n * nums[n-k]);
            maxVal = max(maxVal, dp[k]);
        }
        return maxVal;
    }
};

//  using dp plus space optimization
class Solution {
public:
    
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size(), sum=0, f0 = 0;

        for(int i=0; i<n; i++ ){
            sum += nums[i];
            f0 += i * nums[i];
        }

    
        int maxVal = f0;
        int currF = f0;

        for(int k=1; k<n; k++){
            int newF = currF + sum - (n * nums[n-k]);
            
            maxVal = max(maxVal, newF);
            currF = newF;
        }
        return maxVal;
    }
};
// Approach 3
class Solution {
public:
    
    int maxRotateFunction(vector<int>& nums) {
        
        long sum=0;
        long  F=0;
        for(int i=0;i<nums.size();i++)
        {
            sum+=nums[i];
            F+=(long)i*nums[i];
        }
        int n=nums.size();

        long result=F;
          for(int k = 1; k < nums.size(); k++) {
            F = F + sum - (long)n * nums[n - k];
            
            result = max(result, F);
        }
        return (int)result;
        
    }
};

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int f = 0, n = nums.size();
        int numSum = accumulate(nums.begin(), nums.end(), 0);
        for (int i = 0; i < n; i++) {
            f += i * nums[i];
        }
        int res = f;
        for (int i = n - 1; i > 0; i--) {
            f += numSum - n * nums[i];
            res = max(res, f);
        }
        return res;
    }
};