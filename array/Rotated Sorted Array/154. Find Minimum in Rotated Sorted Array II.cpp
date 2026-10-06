class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int l =0, r=n-1;
        int idx = n-1;
        while(l <= r) {
            while(l < r && nums[l] == nums[l+1]) l++;
            while(l < r && nums[r] == nums[r-1]) r--;
            int m = l + (r-l)/2;

            if(nums[m] < nums[idx]) {
                idx = m;
            }

            if(nums[m] > nums[r]) {
                l = m + 1 ;
            }else {
                r = m - 1 ;
            }
        }
        return nums[idx];
    }
};