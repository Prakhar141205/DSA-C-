class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        if(n < 3) return {{}};
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        for(int i=0; i<n; i++){

            if(i > 0 && nums[i] == nums[i-1]) continue; // skip equal values
            int l=i+1, r = n-1;
            int target = -1*nums[i] ;
            while(l < r){
                if(target > nums[l] + nums[r]) l++;
                else if(target < nums[l] + nums[r]) r--;
                else {

                    while(l < r && nums[l] == nums[l+1]) l++; // skip same values
                    while(l < r && nums[r] == nums[r-1]) r--;

                    ans.push_back({nums[i] , nums[l] , nums[r]});

                    l++;
                    r--;
                }
            }

        }
        return ans;      
    }
};