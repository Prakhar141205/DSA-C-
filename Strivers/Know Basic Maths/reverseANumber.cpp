class Solution {
public:
    typedef long long ll;
    int reverse(int x) {    

        ll t = x ;
        if(t < 0) {
            t *= -1 ;
        }

        ll res = 0;
        while(t) {
            int d =  t % 10 ;
            res = res * 10 ;

            if(res > INT_MAX) return 0;
            res += d ;
            t /= 10;
        }
        
        if(x < 0) return -1*res;

        return res;
    }
};