class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();

        int l=0, r=0;
        int currLen = 0;
        int maxLen = 0, zero_cnt=0;
        while(r < n){
            if(nums[r] == 0){
                zero_cnt++;
            }

            if(zero_cnt > k){
                while(zero_cnt > k){
                   if(nums[l] == 0) {
                    zero_cnt--;
                }
                l++;
                currLen--;
                }
                
            }

            
            r++;
            currLen++;
            maxLen = max(maxLen, currLen);


        }
        return maxLen;
    }
};