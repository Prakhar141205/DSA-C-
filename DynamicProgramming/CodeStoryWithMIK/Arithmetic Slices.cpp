class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n  = nums.size();

        int res = 0 ;

        unordered_map<int, int> mp[n]; // array of map

        for(int i=0; i<n; i++) {

            for(int j=0; j<i; j++) {
                 
                int diff = nums[i] - nums[j] ;
                auto it = mp[j].find(diff);

                int cnt_at_j = it == mp[j].end() ? 0 : it->second ; 
                mp[i][diff] += cnt_at_j + 1 ;

                res += cnt_at_j;
            }
        }
        
        return res;
    }
};


class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n=nums.size(), ans=0;
        unordered_map<int,vector<int>> mp;
        for (int i=0;i<n;i++) mp[nums[i]].push_back(i);
        vector<vector<int>> dp(n,vector<int>(n,0));
        for (int i=1;i<n;i++) {
            for (int j=0;j<i;j++) {
                long long prev=nums[j]; prev+=nums[j]; prev-=nums[i];
                if (prev<INT_MIN||prev>INT_MAX) continue;
                if (mp.find((int)prev)==mp.end()) continue;
                for (int k=0;k<mp[prev].size();k++) {
                    if (mp[prev][k]>=j) k=n;
                    else {
                        dp[i][j]+=1+dp[j][mp[prev][k]];
                    }
                }
                ans+=dp[i][j];
            }
        }
        return ans;
    }
};