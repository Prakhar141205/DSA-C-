class Solution {
public:
    typedef long long ll;
    int n ;
    ll t[100001];

    ll solve(vector<vector<int>>& questions, int i) {
        if(i >= n) return 0;
        if(t[i] != -1) return t[i];
        ll take = questions[i][0] + solve(questions, i+questions[i][1]+1) ;
        ll not_take = solve(questions, i+1) ;

        return t[i] = max(take, not_take);
    }
    long long mostPoints(vector<vector<int>>& questions) {
        n = questions.size();
        memset(t, -1, sizeof(t));
        return solve(questions, 0);
    }
};


// Bottom up

class Solution {
public:
    typedef long long ll;
    int n ;
    ll t[100001];
    long long mostPoints(vector<vector<int>>& questions) {
        n = questions.size();
        memset(t, 0, sizeof(t));
        for(int i=n-1; i>=0; i--) {
            ll take = questions[i][0] ;
            if(i + questions[i][1] + 1 < n) {
                take += t[i + questions[i][1] + 1];
            }
            ll not_take = t[i+1] ;
            t[i] = max(take, not_take);
        }
        return t[0];
    }
};