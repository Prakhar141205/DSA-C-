class Solution {
public:
    using ll = long long;

    long long countCommas(long long n) {

        ll ans = 0;
        ll lower = 1000;

        ll commas = 1;

        while(lower <= n) {

            ll upper = 1000 * lower - 1 ;

            if(upper > n) upper = n;

            ll cntNos = upper - lower + 1 ;

            ans += (cntNos * commas);
            lower *= 1000;
            commas++;
        }

        return ans;      
    }
};

class Solution {
public:
    using ll = long long;

    long long countCommas(long long n) {

        ll ans = 0;
        ll lower = 1000;

        while(lower <= n) {

            ans += (n - lower + 1) ;
            lower *= 1000;
        }

        return ans;      
    }
};