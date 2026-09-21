
class Solution {
public:
    int t[21][21] ;

    int solve(int st, int end) {
        if(st > end) return 1;
        if(t[st][end] != -1) return t[st][end] ;

        int ans = 0;
        for(int i=st; i<=end; i++) {

            int left = solve(st, i-1) ;
            int right = solve(i+1, end);

            // multiply because all the left subtrees can paired up to each right subtree
            ans += (left * right);
        }

        return t[st][end] = ans ;
    }
    int numTrees(int n) {
        if(n == 1) return 1 ;
        memset(t, -1, sizeof(t)) ;

        return solve(1, n);
    }
};