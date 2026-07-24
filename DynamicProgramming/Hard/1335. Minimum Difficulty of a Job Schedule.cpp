class Solution {
public:
    int t[11][302];

    int solve(vector<int>& jd, int n, int d, int idx) {
        if(d == 1) {
            return *max_element(begin(jd) + idx, end(jd) ) ;
        }

        if(t[d][idx] != -1 ) return t[d][idx];

        int maxD = INT_MIN;

        int finalResult = INT_MAX ;

        for(int i=idx; i<= n-d; i++) {
            maxD  = max(jd[i], maxD) ;

            int res =  maxD + solve(jd, n, d-1, i+1) ;

            finalResult = min(finalResult, res) ;
        }

        return t[d][idx] = finalResult ;
    }
    int minDifficulty(vector<int>& jd, int d) {

        int n = jd.size();
        if(n < d ) return -1; 
        memset(t, -1 , sizeof(t));
        return solve(jd, n, d, 0) ;
    }
};