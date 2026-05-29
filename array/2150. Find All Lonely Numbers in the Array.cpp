// TC O(N)
// SC O(N)
class Solution {
public:
    vector<int> findLonely(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return arr;
        unordered_map<int, int> mp;
        vector<int> ans;
        for(int i=0; i<n; i++) mp[arr[i]]++;

        for(int i=0; i<n; i++){
            int x = arr[i];
            if(!mp.count(x+1) && !mp.count(x-1) && mp[x] == 1) ans.push_back(x);
        }
        return ans;
    }
};

// using constant space

class Solution {
public:
    vector<int> findLonely(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return arr;
        sort(arr.begin(), arr.end());
        // unordered_map<int, int> mp;
        vector<int> ans;
        // for(int i=0; i<n; i++) mp[arr[i]]++;

        for(int i=1; i<n-1; i++){
            int diffN = abs(arr[i] - arr[i+1]);
            int diffP =abs(arr[i] - arr[i-1]);
            if(diffN >= 2 && diffP >= 2) ans.push_back(arr[i]);
        }

       int diff01 = abs(arr[0] - arr[1]);
       int diffL = abs(arr[n-1] - arr[n-2]);

       if(diff01 >= 2) ans.push_back(arr[0]);
       if(diffL >= 2) ans.push_back(arr[n-1]);
        return ans;
    }
};

#pragma GCC optimize("Ofast,unroll-loops,inline")
#include <vector>

static const int speedup = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    vector<int> findLonely(vector<int>& nums) {
        int n = nums.size();
        if(n== 1) return nums;
        sort(nums.begin(), nums.end());
        vector<int> ans;
        ans.reserve(n);
        if(nums[1] != nums[0] && abs(nums[1]-nums[0]) != 1) ans.push_back(nums[0]);
        
        for(int i=1; i<n-1; i++){
            int prev = nums[i-1];
            int nxt = nums[i+1];
            int crr = nums[i];
            if(prev == crr || nxt == crr || abs(prev-crr)== 1 || abs(nxt-crr) == 1) continue;
            ans.push_back(crr);
            
        }
        if(nums[n-1] != nums[n-2] && abs(nums[n-1]-nums[n-2]) != 1) ans.push_back(nums[n-1]);
        return ans;
    }
};