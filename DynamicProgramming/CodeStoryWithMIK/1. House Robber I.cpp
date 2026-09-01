// Tabulation ===> Bottom Up

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> t(n+1, 0);
        
        t[1] = nums[0];

        for(int i=2; i<=n; i++) {

            t[i] = max(nums[i-1] + t[i-2], t[i-1]);
        }
        return t[n];
    }
};

// Memoization ===> Top Down Approach 

class Solution {
public:
    int n ;
    int t[101] ;
    int solve(vector<int>& nums, int i) {
        if(i >= n ) return 0;
        if(t[i] != -1 ) return t[i];
        int take = nums[i] + solve(nums, i+2);
        int skip = solve(nums, i+1);

        return t[i] = max(take, skip);
    }
    int rob(vector<int>& nums) {
        n = nums.size();
        if(n == 1) return nums[0];
        memset(t, -1, sizeof(t));
        return solve(nums, 0);
    }
};