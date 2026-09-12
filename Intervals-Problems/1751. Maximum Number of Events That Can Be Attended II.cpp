// class Solution {
// public:
//     vector<vector<int>> t;
//     int n;
//     // custom binary search
//     int getNextIndex(vector<vector<int>>& vec, int l, int currEndTime) {
//         int r = n-1 ;
//         int res = n ;
//         while(l <= r) {
//             int mid = l + (r-l)/2 ;

//             if((vec[mid])[0] >= currEndTime) {
//                 res = mid;
//                 r = mid - 1 ;
//             }else {
//                 l = mid + 1;
//             }
//         }

//         return res;
//     }
//     int solve(vector<vector<int>>& events, int i, int k) {
//         if(i >= n || k <= 0) return 0;
//         if(t[i][k] != -1) return t[i][k];


//         int skip = solve(events, i+1, k);
        
//         // using custom lambda comparator as the fourth argument 
//         // auto lambda  = [&(auto& a, auto& b) {
//         //     return a[0] < b[0];
//         // }
//         // int nextIndex = upper_bound(events.begin(), events.end(), vector<int> {events[i][1], INT_MAX, INT_MAX}) - events.begin();
//         int nextIndex = getNextIndex(events, i, events[i][1]);
//         int take = events[i][2] + solve(events, nextIndex, k-1);
//         return t[i][k] = max(take, skip);
//     }
//     int maxValue(vector<vector<int>>& events, int k) {
//         n = events.size();
//         sort(events.begin(), events.end());
//         t.resize(n+1, vector<int> (k+1, -1));

//         return solve(events, 0, k);
//     }
// };

class Solution {
public:
    vector<vector<int>> t;
    int n;

    int solve(vector<vector<int>>& events, int i, int k) {
        if(i >= n || k <= 0) return 0;
        if(t[i][k] != -1) return t[i][k];

        int skip = solve(events, i+1, k);
        
        // Optimize target: Only store what the comparator checks
        vector<int> target = {events[i][1]}; 

        // CRITICAL FIX: Pass 'a' and 'b' by const reference (&) to avoid TLE copies
        int nextIndex = upper_bound(
            events.begin() + i + 1, 
            events.end(), 
            target, 
            [](const vector<int>& a, const vector<int>& b) {
                return a[0] < b[0]; 
            }
        ) - events.begin();

        int take = events[i][2] + solve(events, nextIndex, k-1);
        return t[i][k] = max(take, skip);
    }

    int maxValue(vector<vector<int>>& events, int k) {
        n = events.size();
        sort(events.begin(), events.end()); // Sorts by start time
        t.resize(n + 1, vector<int>(k + 1, -1));

        return solve(events, 0, k);
    }
};
