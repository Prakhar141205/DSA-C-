class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {

        int n = points.size();

        sort(points.begin(), points.end());

        int cnt = 1; // assumed first ballon needs a arrow to burst it.

        int prevS = points[0][0];
        int prevE = points[0][1];

        for(int i=1; i<n; i++) {
            // no overlap
            int currS = points[i][0];
            int currE = points[i][1];

            if(prevE < currS) {
                cnt++; // need a arrow to burst

                // update the previous
                prevS = currS;
                prevE = currE;
            }else {
                // overlap

                prevS = max(prevS, currS);
                prevE = min(prevE, currE);

            }
        }
        return cnt;
    }
};


class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](auto &a,auto &b){
            if(a[0]==b[0])
              return a[1]>b[1];
            return a[0]<b[0];
        });
        int result=0;
        int right=0;
        for(auto &v: intervals){
            if(v[1]>right){
                result++;
                right=v[1];
            }
        }
        return result;
    }
};