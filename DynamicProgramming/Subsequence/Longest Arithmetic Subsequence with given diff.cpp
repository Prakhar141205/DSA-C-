class Solution {
public:
    int n ;

    int D;
    int t[100001];

    int solve(int i, vector<int>& arr) {
        if(t[i] != -1) return t[i];
        int ans = 0;

        for(int j=i+1; j<n; j++) {
            if(arr[j] - arr[i] == D)
                ans = max(ans, 1 + solve(j, arr));
        }

        return t[i] = ans;
    }
    int longestSubsequence(vector<int>& arr, int diff) {
        n = arr.size();
        memset(t, -1, sizeof(t));
        D = diff;
        int res = 0;
        for(int i=0; i<n; i++) {
            res = max(res, 1 + solve(i, arr));
        }

       return res; 
    }
};

// Optimal Approach using HashMap
class Solution {
public:
    int n ;
    int longestSubsequence(vector<int>& arr, int diff) {
        n = arr.size();
        unordered_map<int, int> mp; // last element of subsequence, length of the subs

        for(int i=0; i<n; i++) {
            if(i == 0 || mp.find(arr[i] - diff) == mp.end()) {
                mp[arr[i]] = 1;
            } else {
                mp[arr[i]] = mp[arr[i] - diff] + 1;
            }
        }

        auto maxEle = max_element(mp.begin(), mp.end(), [](auto& p1, auto& p2) {
            return p1.second < p2.second;
        });
       return maxEle->second; 
    }
};