class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> t(n) ;
        t[0] = 1 ; // first ugly number 
        /*

        state definition 
        t[i] contains i+1 th ugly number
        
        */
        int i2 = 0, i3 = 0, i5 = 0  ;

        for(int i=1; i<n; i++) {

            int next = min({t[i2]*2, t[i3]*3, t[i5]*5});

            t[i] = next ;

            if(t[i2]*2 == next) i2++;
            if(t[i3]*3 == next) i3++;
            if(t[i5]*5 == next) i5++;
        }

        return t[n-1] ;
    }
};