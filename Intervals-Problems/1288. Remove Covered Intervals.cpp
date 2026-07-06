class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n == 1) return 1;
        int cnt = 1;


        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            if(a[0] == b[0]){
                return a[1] > b[1];

            }
            return a[0] < b [0]; 
        });

        int st = intervals[0][0];
        int end = intervals[0][1];

        vector<vector<int>> res;

        // res.push_back(intervals[0]);

        for(int i=1; i<n; i++) {
            if(intervals[i][0] >= st && intervals[i][1] <= end) {

                    st = min(intervals[i][0], st);
                    end = max(intervals[i][1], end);
                    continue;
                   
                }else {
                    cnt++;
                    st = intervals[i][0];
                    end = intervals[i][1];
                }
                
                // res.push_back(intervals[i]);
        }

        // return res.size();
        return cnt;
        
    }
};