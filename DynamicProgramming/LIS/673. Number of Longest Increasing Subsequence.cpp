class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();

        vector<int> t(n, 1), cnt(n, 1);
        for(int i=0; i<n; i++) {

            for(int j=0; j<i; j++) {

               if(nums[j] < nums[i]) {
                 if(t[j] + 1 == t[i]) {
                    cnt[i] += cnt[j];
                }else if(t[j] + 1 > t[i]) {
                    t[i] = t[j] + 1 ;
                    cnt[i] = cnt[j];
                }
               }
            }
        }

        int length_lis = *max_element(begin(t), end(t));
         
        int ans = 0;
        for(int i=0; i<n; i++) {
            if(t[i] == length_lis) {
                ans += cnt[i];
            }
        }

        return ans;
    }
};

class Solution {
public:
    int maxLen = 0;
    int count = 0;

    void solve(int i, int prev, vector<int>& nums, int len) {

        if (i == nums.size()) {

            if (len > maxLen) {
                maxLen = len;
                count = 1;
            }
            else if (len == maxLen) {
                count++;
            }

            return;
        }

        // Don't take nums[i]
        solve(i + 1, prev, nums, len);

        // Take nums[i]
        if (prev == -1 || nums[i] > nums[prev]) {
            solve(i + 1, i, nums, len + 1);
        }
    }

    int findNumberOfLIS(vector<int>& nums) {
        solve(0, -1, nums, 0);
        return count;
    }
};

class Solution {
public:

    vector<vector<pair<int,int>>> dp;
    vector<vector<bool>> vis;

    pair<int,int> solve(int i, int prev, vector<int>& nums) {

        if (i == nums.size()) {
            return {0, 1};
        }

        if (vis[i][prev + 1]) {
            return dp[i][prev + 1];
        }

        vis[i][prev + 1] = true;

        // Don't take
        pair<int,int> notTake = solve(i + 1, prev, nums);

        // Take
        pair<int,int> take = {0, 0};

        if (prev == -1 || nums[i] > nums[prev]) {

            pair<int,int> temp = solve(i + 1, i, nums);

            take.first = 1 + temp.first;
            take.second = temp.second;
        }

        pair<int,int> ans;

        if (take.first > notTake.first) {
            ans = take;
        }
        else if (notTake.first > take.first) {
            ans = notTake;
        }
        else {
            ans = {
                take.first,
                take.second + notTake.second
            };
        }

        return dp[i][prev + 1] = ans;
    }

    int findNumberOfLIS(vector<int>& nums) {

        int n = nums.size();

        dp.resize(n, vector<pair<int,int>>(n + 1));
        vis.resize(n, vector<bool>(n + 1, false));

        return solve(0, -1, nums).second;
    }
};