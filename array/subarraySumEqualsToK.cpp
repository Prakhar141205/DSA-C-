class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m; // currsum, cnt
        m[0]=1;
        int n = nums.size();
        
        
        int currSum=0, ans=0;
        for(int r=0; r<n; r++){
            currSum += nums[r];
            int remSum= currSum-k;

            ans += m[remSum];

            m[currSum] += 1;
            
        }
        return ans;
    }
};