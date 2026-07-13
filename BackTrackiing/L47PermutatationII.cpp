oclass Solution {
public:
    unordered_map<int, int> mp;
    vector<vector<int>> ans;
    int n ;
    void solve(vector<int>& temp) {
        if(temp.size() >= n) {
            ans.push_back(temp);
            return;
        }

        for(auto& [num, cnt] : mp) {
            if(cnt == 0) continue;

            temp.push_back(num);
            mp[num]--;

            solve(temp);

            temp.pop_back();
            mp[num]++;
        }


    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        n = nums.size();
        for(int& x : nums) mp[x]++;

        vector<int> temp;
        solve(temp);

        return ans;
        
    }
};

// Approach 2

class Solution {
public:
    vector<vector<int>> ans;       
    int n ;
    void solve(int index, vector<int>& nums) {
        if(index == n) {
            ans.push_back(nums);
            return;
        }

        unordered_set<int> st;
        for(int i=index; i<n; i++) {
            if(st.find(nums[i]) != st.end()) continue;

            st.insert(nums[i]);
            swap(nums[index], nums[i]);
            solve(index+1, nums);
            swap(nums[index], nums[i]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        n = nums.size();
        solve(0, nums);         
        return ans;
    }
};