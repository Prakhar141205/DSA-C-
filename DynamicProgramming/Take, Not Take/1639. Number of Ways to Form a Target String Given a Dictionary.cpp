class Solution {
public:
    const int mod = 1e9+7 ;
    int m, k ;
    int t[1001][1001] ;

    int solve(int i, int j, vector<vector<long long>>& freq, string& target) {
        if(i == m) return 1;
        if(j >= k) return 0;

        if(t[i][j] != -1) return t[i][j];
        int not_taken = solve(i, j+1, freq, target) % mod;
        int taken = (freq[target[i] - 'a'][j] * solve(i+1, j+1, freq, target)) % mod ;

        return t[i][j] = (taken + not_taken) % mod ; 
    }
    int numWays(vector<string>& words, string target) {
        m = target.length();
        k = words[0].length();
        memset(t, -1, sizeof(t));
        vector<vector<long long>> freq(26, vector<long long> (k, 0)) ;

        for(int col = 0; col < k; col++) {

            for(string& word : words) {
                char ch = word[col];
                freq[ch - 'a'][col]++;

            }
        }
        
        return solve(0, 0, freq, target);
    }
};

// Bottom up
class Solution {
public:
    const int mod = 1e9+7 ;
    int m, k ;
    int numWays(vector<string>& words, string target) {
        m = target.length();
        k = words[0].length();
        vector<vector<long long>> freq(26, vector<long long> (k, 0)) ;

        for(int col = 0; col < k; col++) {

            for(string& word : words) {
                char ch = word[col];
                freq[ch - 'a'][col]++;

            }
        }
        vector<vector<int>> t(m+1, vector<int> (k+1, 0)) ;
        t[0][0] = 1 ; 
        /*
        // target = "" ==> possible to make using one way

        // fill the first col to be zero

        // not_take = t[i][j+1];
        // taken = freq[target[i] - 'a'][j] * t[i+1][j+1] ;

        // t[i][j] ===> total ways of forming target of length i using words in dict of length of j

        */
        for(int i=0; i<=m; i++) {

            for(int j=0; j<=k; j++) {
                
                if(j < k)
                    t[i][j+1] = (t[i][j+1] + t[i][j]) % mod ;

                if(i < m && j < k)
                t[i+1][j+1] = (t[i+1][j+1] + t[i][j] * freq[target[i] - 'a'][j]) % mod ;
            }
        }
        return t[m][k];
    }
};

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

        int i_crime_did = solve(i+1, min(mP, cP + pr[i]), people + gp[i], mP, gp, pr);
        int i_crime_not_did = solve(i+1, cP, people, mP, gp, pr);

        return t[i][cP][people] = i_crime_did + i_crime_not_did ;
    }
    int profitableSchemes(int n, int mP, vector<int>& gp, vector<int>& pr) {
        N = n;
        memset(t, -1, sizeof(t));
        return solve(0, 0, 0, mP, gp, pr);
    }
};