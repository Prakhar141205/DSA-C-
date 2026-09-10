class Solution {
public:
    struct VectorHash {
        size_t operator()(const vector<int>& v) const {
            size_t hash = 0;

            for(int x : v)
                hash = hash * 31 + x;

            return hash;
        }
    };

    int n;
    unordered_map<vector<int>, int, VectorHash> mp;

    int solve(vector<int>& nums, int ops, vector<int>& used) {
        if(ops > n / 2)
            return 0;

        if(mp.find(used) != mp.end())
            return mp[used];

        int maxScore = 0;

        for(int i = 0; i < n - 1; i++) {
            if(used[i])
                continue;

            for(int j = i + 1; j < n; j++) {
                if(used[j])
                    continue;

                used[i] = 1;
                used[j] = 1;

                int sum = ops * __gcd(nums[i], nums[j]);

                int sum_ = solve(nums, ops + 1, used);

                maxScore = max(maxScore, sum + sum_);

                used[i] = 0;
                used[j] = 0;
            }

        
        }

        return mp[used] = maxScore;
    }

    int maxScore(vector<int>& nums) {
        n = nums.size();

        vector<int> used(n, 0);

        mp.clear();

        return solve(nums, 1, used);
    }
};