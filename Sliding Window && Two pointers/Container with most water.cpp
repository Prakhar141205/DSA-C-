class Solution {
public:
    int maxArea(vector<int>& nums) {
        int n = nums.size();

        int l=0, r= n-1;
        int ans = 0;
        while(l < r){
            // compare the trapped water
            int curr = min(nums[l], nums[r]) * (r-l);
            ans = max(ans, curr);

            // greedily keeps the pointer which is at the maximum height 
            // so that later we get the maximum water
            if(nums[l] >= nums[r]){
                r--;
            }else {
                l++;
            }

        }

        return ans;
        
    }
};