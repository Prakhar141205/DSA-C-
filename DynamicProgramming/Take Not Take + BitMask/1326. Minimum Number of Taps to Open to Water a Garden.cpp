class Solution {
public:
    map<pair<int, int>, int> mp;

    int solve(int n, vector<pair<int, int>>& range, int i, int maxEnd) {

        if(mp.find({i, maxEnd}) != mp.end()) {
                return mp[{i, maxEnd}];
        }
        if(i >= range.size()) {

            if(maxEnd >= n) {
                return 0; // means all the garden is watered
            }else {
                return 1e9; // it is not possible to water the entire garden in this way
            }
        }
            if(range[i].first > maxEnd) { // there is gap created between two garden 
                return 1e9;
            }

            int open = 1 + solve(n, range, i+1, max(maxEnd, range[i].second));
            int not_open = solve(n, range, i+1, maxEnd);
            
            
        return mp[{i, maxEnd}] = min(open, not_open) ;
    }
    int minTaps(int n, vector<int>& ranges) {
        int x = ranges.size();
        mp.clear();
        vector<pair<int, int>> range; 
        for(int i=0; i<x; i++) {
            range.push_back({max(0, i-ranges[i]), min(n, i + ranges[i])});
        }

        sort(begin(range), end(range));
        int ans = solve(n, range, 0, 0) ;
        return ans == 1e9 ? -1 : ans;
    }
};