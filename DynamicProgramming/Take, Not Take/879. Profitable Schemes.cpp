class Solution {
public:
    const int mod = 1e9 + 7 ;
    int N;

    int t[101][101][101] ;

    int solve(int i, int cP, int people, int& mP, vector<int>& gp, vector<int>& pr) {

        if(people > N) return 0;

        if(t[i][cP][people] != -1) return t[i][cP][people] ;
        if(i == gp.size()) {
            if(cP >= mP) return 1 ;

            return 0;
        }

        int i_crime_did = solve(i+1, min(mP, cP + pr[i]), people + gp[i], mP, gp, pr) % mod;
        int i_crime_not_did = solve(i+1, cP, people, mP, gp, pr) % mod;

        return t[i][cP][people] = (i_crime_did + i_crime_not_did) % mod ;
    }
    int profitableSchemes(int n, int mP, vector<int>& gp, vector<int>& pr) {
        N = n;
        memset(t, -1, sizeof(t));
        return solve(0, 0, 0, mP, gp, pr);
    }
};