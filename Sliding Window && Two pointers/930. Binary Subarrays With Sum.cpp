class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int l=0, r=0, cnt=0;
        int n = nums.size();
        int currSum = 0;
        int prefix_zeros = 0;
        while(r < n){
            currSum += nums[r];

            while(l < r && (nums[l] == 0 || currSum > goal)){
                if(nums[l] == 0){
                    prefix_zeros += 1;
                }else prefix_zeros = 0;

                currSum -= nums[l];
                l++;
            }
            if(currSum == goal){
                cnt += 1 + prefix_zeros;
            }
            r++;
        }
        
        return cnt;
    }
};