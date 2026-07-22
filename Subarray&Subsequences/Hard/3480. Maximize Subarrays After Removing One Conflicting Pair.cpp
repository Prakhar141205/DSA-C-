class Solution {
public:
    typedef long long ll;
    #define ALL(x) begin(x), end(x) 

    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        ll valid = 0;
        
        vector<vector<int>> conflictindPoints(n+1);
        // conflicting[i] = {points which conflict with i}
        for(auto& p : conflictingPairs) {

            int a = min(p[0], p[1]);
            int b = max(p[0], p[1]);

            conflictindPoints[b].push_back(a);
        }
        int maxConflict = 0;
        int secMaxConflict = 0;

        vector<ll> extra(n+1, 0);
        // no of extra subarray by removing the i conflicting

        // total array ending at point i 
        for(int end=1; end <= n; end++) {

            for(int& u : conflictindPoints[end]) {
                if(u >= maxConflict){
                    secMaxConflict = maxConflict;
                    maxConflict = u;
                }else if( u > secMaxConflict){
                    secMaxConflict = u;
                }
            }

            valid += end - maxConflict ;

            extra[maxConflict] += maxConflict - secMaxConflict ;

        }

        return valid + *(max_element(ALL(extra)));

    }   
};