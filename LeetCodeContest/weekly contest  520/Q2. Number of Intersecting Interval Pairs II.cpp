class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<int> starts(n);
        vector<int> ends(n);
        for (int i = 0; i < n; i++) {
            starts[i] = intervals[i][0];
            ends[i] = intervals[i][1]; 
        }

        sort(begin(starts), end(starts)) ;
        sort(begin(ends), end(ends)) ;
        long long non_i = 0 ;

        
        for(int i=0; i<n-1; i++) {
            int ed = ends[i];
            auto nextIdx = upper_bound(begin(starts), end(starts), ed) - begin(starts);

            non_i += (n-nextIdx) ;

            
        }
        long long total = (long long)n * (n-1) /  2 ;
        return total - non_i ;
    }
};

/*
class Solution {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals) {
        
        int n = intervals.size();
        sort(begin(intervals), end(intervals)) ;
        int ans = 0 ;
        for(int i=0; i<n-1; i++) {
            int end = intervals[i][1];

            for(int j=i+1; j<n; j++) {

                if(end >= intervals[j][0]) {
                    ans += 1;
                }
            }
        }

        return ans ;
    }
};©leetcode*/