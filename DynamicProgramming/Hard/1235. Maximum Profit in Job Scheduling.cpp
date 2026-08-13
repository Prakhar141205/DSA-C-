class Solution {
public:
    int n ;
    int getNextIndex(vector<tuple<int, int, int>>& vec, int l, int currEndTime) {
        int r = n-1 ;
        int res = n ;
        while(l <= r) {
            int mid = l + (r-l)/2 ;

            if(get<0> (vec[mid]) >= currEndTime) {
                res = mid;
                r = mid - 1 ;
            }else {
                l = mid + 1;
            }
        }

        return res;
    }
    int t[50001] ;
    int solve(vector<tuple<int, int, int>>& vec, int i) {
        if(i >= n) return 0 ;

        if(t[i] != -1) return t[i];
        
        int next = getNextIndex(vec, i, get<1> (vec[i])) ;

        int taken = get<2> (vec[i]) + solve(vec, next);
        int not_taken = solve(vec, i+1);

        return t[i] = max(taken, not_taken);
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        n = startTime.size();
        vector<tuple<int, int, int>> vec(n);
        memset(t, -1, sizeof(t));
        for(int i=0; i<n; i++) {
            int st = startTime[i];
            int et = endTime[i];
            int pr = profit[i];

            vec[i] = {st, et, pr} ;
        }

        sort(begin(vec), end(vec), [&](auto& t1, tuple<int, int, int>& t2) {
                return get<0> (t1) < get<0> (t2) ;
        });

        return solve(vec, 0) ;
    }
};