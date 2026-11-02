class Solution {
public:
    int minMoves2(vector<int>& nums) {
        
        sort(begin(nums), end(nums));

        int n = nums.size();
        int median;
        if(n&1) {
            median = nums[n/2];
        }else {
            int sum = nums[n/2] + nums[n/2-1];
            median = (sum&1 ) ? (sum+1)/2 : sum / 2 ;
        }
        int ans = 0;
        for(int x : nums) {
            ans += abs(x - median);
        }

        return ans;
    }
};