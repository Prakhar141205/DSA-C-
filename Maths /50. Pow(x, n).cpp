class Solution {
public:
    double solve(double x, long long n) {
        if(n == 0) return 1;
        if(n < 0) return solve(1.0/x, -1*n);
        if(n&1) return x * solve(x*x, (n-1)/2);
        return solve(x*x, n/2);
    }
    double myPow(double x, int n) {
        return solve(x, (long long)n);
    }
};

class Solution {
public:
    double myPow(double x, int n) {

        long long N = llabs((long long)n);

        double ans = 1;

        while (N > 0) {

            if (N & 1) {
                ans *= x;
            }

            x *= x;
            N >>= 1;
        }

        return n < 0 ? 1 / ans : ans;
    }
};