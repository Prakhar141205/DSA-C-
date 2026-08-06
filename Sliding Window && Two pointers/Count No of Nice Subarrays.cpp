class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size() ;
        int odd_cnt = 0;
        int prev_cnt = 0;
        int l=0, r=0;
        int ans = 0 ;
        while(r < n) {
            if(nums[r] & 1) {
                odd_cnt++;
                prev_cnt = 0;
            }

            while(odd_cnt == k) {
                prev_cnt++;

                if(nums[l] & 1) {
                    odd_cnt--;
                }

                l++;
            }

            ans += prev_cnt ;
            r++;
        }

        return ans ;
    }
};
