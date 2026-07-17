class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // patience sorting ==> best for the subsequence finding or the length of the largest subsequence
        
        int n = nums.size();
        vector<int> sorted;
        sorted.push_back(nums[0]);

        for(int x = 1; x < n; x++) {
            auto it = lower_bound(sorted.begin(), sorted.end(), nums[x]) ;

            if(it == sorted.end()) {
                sorted.push_back(nums[x]);
                
            }else {
                *it = nums[x];
            }
        }

        return sorted.size();
    }
};