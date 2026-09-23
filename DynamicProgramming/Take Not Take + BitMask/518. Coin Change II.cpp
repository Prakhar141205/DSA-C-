class Solution {
public:
    int n ;
    int t[301][5001];

    int solve(int i, int amnt, vector<int>& coins) {
        if(amnt == 0) return 1;
        if(amnt < 0 ) return  0;
        if(i >= n) return 0 ;
        if(t[i][amnt] != -1) return t[i][amnt];
        int take = solve(i, amnt-coins[i], coins);
        int not_take = solve(i+1, amnt, coins);
        return t[i][amnt] = take + not_take ;
    }
    int change(int amount, vector<int>& coins) {
        n = coins.size();
        memset(t, -1, sizeof(t)) ;
        return solve(0, amount, coins);
    }
};