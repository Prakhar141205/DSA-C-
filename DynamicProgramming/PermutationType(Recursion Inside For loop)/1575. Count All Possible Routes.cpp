class Solution {
public:
    int  mod = 1e9+7;
    int n ;
    int t[101][201];

    int solve(vector<int>& locations, int st, int finish, int fuel) {
        if(fuel < 0 ) return 0;
        int ans = 0;
        if( t[st][fuel] != -1) return t[st][fuel]; 
        if(st == finish) {
            ans += 1;
        }


        for(int i=0; i<n; i++) {

            if(st != i) {

                ans = (ans + solve(locations, i, finish, fuel - (abs(locations[i]-locations[st])))) % mod ;
            }
        }

        return t[st][fuel] =    ans%mod;
    }
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        n = locations.size();
        memset(t, -1, sizeof(t));
        return solve(locations, start, finish, fuel);
    }
};