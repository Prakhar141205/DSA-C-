class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        auto it = *max_element(nums.begin(), nums.end());
        int l=0,r=0;
        int cnt = 0;
        long long ans=0;
        while(r < n) {
            if(nums[r] == it) {
                cnt++;
            }
            // decrease the window size
            while(cnt >= k) {
                ans += (n-r) ;

                if(nums[l] == it){
                    cnt--;
                }
                
                l++;
            }

            r++;
        } 
        return ans;
    }
};

// approach 2 
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        auto it = *max_element(nums.begin(), nums.end());

        vector<int> last_seen_idx;

        int l=0,r=0;

        long long ans=0;
        while(r < n) {
            if(nums[r] == it) {
                last_seen_idx.push_back(r);
            }
            // decrease the window size
            int z = last_seen_idx.size();
            if(z >= k) {
                int lsi = last_seen_idx[z - k];
                cout << lsi << " ";
                ans += (lsi + 1) ;
                cout << ans << " ";
            }

            r++;
        } 
        return ans;
    }
};