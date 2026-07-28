class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();

        vector<int> freeTime ;
        freeTime.push_back(startTime[0]);

        for(int i=1; i<n; i++) {
            freeTime.push_back(startTime[i] - endTime[i-1]);
        }

        freeTime.push_back(eventTime - endTime[n-1]);

        int l=0, r =0;
        int ans = INT_MIN;
        int sum = 0;
        int f = freeTime.size();
        while(r < f) {
            sum += freeTime[r];

            if(l < f && r-l+1 > k+1) {
                sum -= freeTime[l];
                l++;
            }
            ans = max(sum, ans);
            r++;
        }
        return ans ;
    }
};