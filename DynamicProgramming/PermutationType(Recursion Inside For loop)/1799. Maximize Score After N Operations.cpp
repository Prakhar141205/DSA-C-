class Solution {
public:
    int n;
    int solve(vector<int>& nums, int ops, vector<int>& used) {
        // if(ops > n/2) return 0;

        int maxScore = 0;
        for(int i=0; i<n-1; i++ ) {

            if(used[i]) continue;
            for(int j=i+1; j<n; j++) {

                if(used[j]) continue;

                used[i] = 1;
                used[j] = 1;

                int sum = ops * __gcd(nums[i], nums[j]);
                int sum_ = solve(nums, ops+1, used);
                maxScore = max(maxScore, sum_ + sum);

                used[i] = false;
                used[j] = false;
            }
        }

        return maxScore;
    }
    int maxScore(vector<int>& nums) {
        n = nums.size();
        vector<int> used(n, 0);

        return solve(nums, 1, used);
    }
};