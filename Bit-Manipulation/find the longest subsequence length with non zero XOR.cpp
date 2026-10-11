class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();

        int ans =0;
        bool allZero = true;
        for(int i=0; i<n; i++) {
            if(nums[i] != 0) allZero = false;
            ans ^= nums[i];
        }
        if(allZero ) return 0 ;
        return ans == 0 ? n-1 : n ;
    }
};