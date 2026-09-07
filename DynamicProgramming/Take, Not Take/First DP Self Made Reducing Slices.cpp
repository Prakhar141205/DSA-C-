class Solution {
public:
    int n ;
    int t[502][502];
    int solve(vector<int>& stfs, int i, int time) {
        if(i >= n) return 0;
        if(t[i][time] != -1) return t[i][time];
        int make = time * stfs[i] + solve(stfs, i+1, time+1);
        int not_make = solve(stfs, i+1, time) ;

        return t[i][time] = max(make, not_make );
    }
    int maxSatisfaction(vector<int>& stfs) {
        n = stfs.size();
        int time = 1;
        sort(stfs.begin(), stfs.end()) ;
        memset(t, -1, sizeof(t));

        return solve(stfs, 0, time);
        
    }
};

// Bottom Up

class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(), satisfaction.end());
        
        vector<vector<long long>> t(501, vector<long long>(501,INT_MIN));

        //t[i][j] = max value till 0.....i food and time is j currently
        
        int n = satisfaction.size();
        
        //at time 0, we have no value. i.e. 0 - COOKING NOT YET STARTED
        for(int i=0;i<501;i++){
            t[i][0] = 0;
        }
        
        //COOKING STARTED AT TIME = 1 and le't start with 0th food : t[0][1]
        t[0][1] = satisfaction[0];

        for(int i=1;i<n;i++){
            for(int time = 1;time<=n;time++){
                long long include = satisfaction[i]*time + t[i-1][time-1];
                
                long long exclude = 0 + t[i-1][time];
                
                t[i][time] = max(include,exclude);
            }
        }

        //Since the Qn doesn't ask the maximum value at time = n, but
        //it asks for the maximum value overall at any time. 
        //So, we check the values for all time for 0....n-1 food i.e. last row depicts 0...n-1 (t[n-1])
        long long ans = 0;
        for(int time = 0;time <= n;time++){
            ans = max(ans,t[n-1][time]);
        }

        return ans;
    }
};