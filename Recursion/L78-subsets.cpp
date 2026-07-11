class Solution {
public:
    void solve(vector<int>& nums, int idx, vector<int>& temp, vector<vector<int>>& ans) {

        if(idx >= nums.size()) {
            ans.push_back(temp);
            return ;
        }

        temp.push_back(nums[idx]) ;
        solve(nums, idx+1, temp, ans);

        temp.pop_back();
        solve(nums, idx+1, temp, ans) ;


    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> temp;
        int idx=0;
        solve(nums, idx, temp, ans) ;
        return ans;
        
    }
};