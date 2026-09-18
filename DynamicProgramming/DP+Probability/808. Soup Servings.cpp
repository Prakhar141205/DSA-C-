class Solution {
public:
    double solve(int A, int B) {

        if(A <= 0 && B <= 0) return 0.5 ;
        if(A <= 0) return 1.0;
        if(B <= 0) return 0.0;

        double A_100_B_0 = solve(A-100, B);
        double A_75_B_25 = solve(A-75, B-25);
        double A_50_B_50 = solve(A-50, B-50);
        double A_25_B_75 = solve(A-25, B-75);o

        return (A_100_B_0 + A_75_B_25 + A_50_B_50 + A_25_B_75) / 4.0 ;
    }
    double soupServings(int n) {
        return solve(n ,n );
    }
};

/*

from functools import lru_cache
import math

class Solution:
    def soupServings(self, n: int) -> float:
        if n > 5000:
            return 1.0
        units = math.ceil(n / 25)

        @lru_cache(None)
        def calc_prob(soupA, soupB):
            if soupA <= 0 and soupB <= 0:
                return 0.5
            if soupA <= 0:
                return 1.0
            if soupB <= 0:
                return 0.0
            return 0.25 * (
                calc_prob(soupA - 4, soupB) +
                calc_prob(soupA - 3, soupB - 1) +
                calc_prob(soupA - 2, soupB - 2) +
                calc_prob(soupA - 1, soupB - 3)
            )

        return calc_prob(units, units)
        
*/