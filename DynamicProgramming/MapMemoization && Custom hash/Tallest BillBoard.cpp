class Solution {
public:
    int totalSum = 0;
    int n;
    int solve(vector<int>& rods, int i, int left, int right) {
        if(i >= n) {
            if(left == right) {
                return left;
            }else {
                return 0;
            }
        }

        
        int dontUse = solve(rods, i+1, left, right);
        int addToleft = solve(rods, i+1, left + rods[i], right);
        int addToRight = solve(rods, i+1, left, right+rods[i]);

        return max({dontUse, addToRight, addToleft});
    }
    int tallestBillboard(vector<int>& rods) {
        n = rods.size();

        
        return solve(rods, 0, 0, 0);
    }
};

// Memoization incase of parameterized recursion
class Solution {
public:
    int totalSum = 0;
    int n;
    int t[21][10002];
    int solve(vector<int>& rods, int i, int diff) {
        if(i == n) {
            return (diff == 0 ? 0 : INT_MIN);
        }

        if(t[i][diff + 5000] != -1) return t[i][diff + 5000];

        int dontUse = solve(rods, i+1, diff);
        int addToleft = rods[i] + solve(rods, i+1, diff + rods[i]);
        int addToRight = rods[i] + solve(rods, i+1, diff - rods[i]);

        return t[i][diff + 5000] = max({dontUse, addToRight, addToleft});
    }
    int tallestBillboard(vector<int>& rods) {
        n = rods.size();
        memset(t, -1, sizeof(t));
        
        return solve(rods, 0, 0) / 2 ;
    }
};