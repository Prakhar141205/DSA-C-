class Solution {
public:

    int n ;
    vector<int> ans;

    void solve(vector<int>& nums, int idx, vector<int>& temp, int prev) {
        if(idx >= n) {
            if(temp.size() > ans.size()) {
                ans = temp;
                
            }

            return;
        }


        // take condition 
        if(prev == -1 || nums[idx] % prev  == 0 ) {
            temp.push_back(nums[idx]) ;
            solve(nums, idx+1, temp, nums[idx]) ;
            temp.pop_back() ;
        }

        solve(nums, idx+1, temp, prev) ;

    }
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        n = nums.size(); 

        vector<int> temp;

        int prev = -1 ;

        solve(nums, 0, temp, prev) ;
        return ans ;
    }
};

// Bottom up approach
class Solution {
public:

   
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size(); 
        sort(nums.begin(), nums.end() ) ;

        vector<int> dp(n+1, 1) ;
        vector<int> prev_idx(n, -1) ;

        int last_chosen_idx = 0 ;
        int maxL = 1 ;
        
        for(int i=1; i<n; i++) {

            for(int j=0; j<i; j++) {

                if(nums[i] % nums[j] == 0) {

                    if(dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1 ;
                        prev_idx[i] = j ;
                    }

                    if(dp[i] > maxL) {
                        maxL = dp[i];
                        last_chosen_idx = i ;
                    }
 
                }
            }
        }

        vector<int> res;
        while(last_chosen_idx != -1) {
            res.push_back(nums[last_chosen_idx]) ;
            last_chosen_idx = prev_idx[last_chosen_idx];
            
            }
        return res ;
    }
};