class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> mp; // element , freq

   
        int n = nums.size();
        int l=0, r=0;
        int ans=0;
        while(r < n){
            mp[nums[r]]++;

            while(l < r && mp[nums[r]] > k){
                mp[nums[l]]--;
                l++;
            }

            ans = max(ans, r - l + 1);

            r++;
            
        }

        return ans;
        
    }
};

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> mp; // element , freq

   
        int n = nums.size();
        int l=0, r=0;
        int ans=0;
        int culprit=0;

        while(r < n){

            mp[nums[r]]++;

            if(mp[nums[r]] == k+1){
                culprit++; // nums[r] is culprit
            }

            // shrink the window to remove the culprit
            if(culprit > 0){
                mp[nums[l]]--; // found culprit at left side of window

                if(mp[nums[l]] == k){
                    culprit--;
                    
                }
                l++;
            }
            if(culprit == 0)
                        
            
                ans = max(ans, r - l + 1);

            r++;
            
        }

        return ans;
        
    }
};