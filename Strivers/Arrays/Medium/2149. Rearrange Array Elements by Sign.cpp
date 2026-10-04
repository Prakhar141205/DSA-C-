class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        int e = 0, o = 1;
        vector<int> ans(n);
        
        for(int i=0; i<n; i++) {
            if(nums[i] < 0) {
                ans[o] = nums[i];
                o += 2;
            }else {
                ans[e] = nums[i];
                e += 2;
            }
        }

        return ans;
    }
};