class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;

        sort(begin(nums),end(nums));
        int cnt = 0;
        int currMin = nums[0];

        for(int i=1; i<n; i++) {
            if(nums[i] - currMin <= k) {
                continue;
            } 
            else {
                currMin = nums[i];
                cnt++;
            }
            
        
        } 
        return cnt+1;       
    }
};

class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int ans = 0, i = 0, j = 0;

        while (i < n) {
            while (j < n && nums[j] - nums[i] <= k)
                j++;

            ans++;
            i = j;
        }

        return ans;
    }
};

class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        vector<int> freq(100001, 0);

        for (int x : nums)
            freq[x]++;

        int ans = 0, mn = -1;

        for (int x = 0; x <= 100000; x++) {
            if (freq[x] == 0)
                continue;

            if (mn == -1 || x - mn > k) {
                ans++;
                mn = x;
            }
        }

        return ans;
    }
};

class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        multiset<int> st(nums.begin(), nums.end());

        int ans = 0;

        while (!st.empty()) {
            int mn = *st.begin();
            ans++;

            auto it = st.begin();

            while (it != st.end() && *it - mn <= k)
                it = st.erase(it);
        }

        return ans;
    }
};

class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int x : nums)
            pq.push(x);

        int ans = 0;

        while (!pq.empty()) {
            int mn = pq.top();
            ans++;

            while (!pq.empty() && pq.top() - mn <= k)
                pq.pop();
        }

        return ans;
    }
};

class Solution {
public:
    int solve(vector<int>& nums, int idx,
              vector<pair<int, int>>& groups) {
        if (idx == nums.size())
            return groups.size();

        int ans = nums.size();

        for (int i = 0; i < groups.size(); i++) {
            int mn = groups[i].first;
            int mx = groups[i].second;

            int newMn = min(mn, nums[idx]);
            int newMx = max(mx, nums[idx]);

            if (newMx - newMn <= k) {
                groups[i] = {newMn, newMx};

                ans = min(ans, solve(nums, idx + 1, groups));

                groups[i] = {mn, mx};
            }
        }

        groups.push_back({nums[idx], nums[idx]});
        ans = min(ans, solve(nums, idx + 1, groups));
        groups.pop_back();

        return ans;
    }

    int k;

    int partitionArray(vector<int>& nums, int K) {
        k = K;
        vector<pair<int, int>> groups;
        return solve(nums, 0, groups);
    }
};

class Solution {
public:
    bool canPartition(vector<int>& nums, int k, int m) {
        int groups = 0;
        int mn = -1;

        for (int x : nums) {
            if (mn == -1 || x - mn > k) {
                groups++;
                mn = x;
            }
        }

        return groups <= m;
    }

    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int l = 1, r = nums.size();

        while (l < r) {
            int mid = l + (r - l) / 2;

            if (canPartition(nums, k, mid))
                r = mid;
            else
                l = mid + 1;
        }

        return l;
    }
};

