class Solution {
public:
    int cntReqSubArrays(vector<int>& nums, int k) {
        int n = nums.size();
        int l=0,r=0;
        unordered_map<int, int> mp;
        int cnt=0;
        while(r < n) {
            mp[nums[r]]++;

            while(mp.size() > k ) {
                mp[nums[l]]--;
                
                if(mp[nums[l]] == 0) {
                    mp.erase(nums[l]);
                }
                l++;
            }

            cnt = cnt + ((r-l+1));
            r++;
        }
        return cnt;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
     
        return cntReqSubArrays(nums, k) - cntReqSubArrays(nums, k-1) ;
    }
};

// using single pass sliding window 

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
     
        int n = nums.size();
        int l=0,r=0;
        unordered_map<int, int> mp;
        int cnt=0;
        int l_bada = 0;
        while(r < n) {
            mp[nums[r]]++;

            // shrinking the window
            while(mp.size() > k ) {
                mp[nums[l]]--;
                
                if(mp[nums[l]] == 0) {
                    mp.erase(nums[l]);
                }
                l++;
                l_bada = l ;
            }
            while(mp[nums[l]] > 1) {
                mp[nums[l]]--;
                l++;
            }
            if(mp.size() == k) {
                cnt += (l - l_bada + 1);
            }
            
            r++;
        }
        return cnt;
    }
};