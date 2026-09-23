class Solution {
public:
    int n;
    int t[100001];

    bool solve(vector<int>& nums, int i) {
        if(i >= n) return true;
        if(t[i] != -1) return t[i];

        bool isValidPartition = false;

        // rule 1

        if(i + 1 < n && nums[i] == nums[i+1]) {
            isValidPartition = solve(nums, i+2) ;
            if(isValidPartition) return t[i] = true;
            
        }

        if(i+2 < n && (nums[i] == nums[i+1]) && (nums[i+1] == nums[i+2])) {
            isValidPartition = solve(nums, i+3);
            if(isValidPartition) return t[i] = true;
        }

        if(i+2 < n && (nums[i+1] - nums[i] == 1 ) && (nums[i+2] - nums[i+1] == 1) ) {
            isValidPartition = solve(nums, i+3) ;
            if(isValidPartition) return t[i] = true;
        }

        return t[i] = isValidPartition;
    }
    bool validPartition(vector<int>& nums) {
        n = nums.size();
        memset(t, -1, sizeof(t));
        return solve(nums, 0);
    }
};