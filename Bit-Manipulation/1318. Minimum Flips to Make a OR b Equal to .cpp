class Solution {
public:
    int minFlips(int a, int b, int c) {
        int flips = 0;

        while(a || b || c){

            if(c & 1) { // c MSB is 1
                if(!(a&1) && !(b & 1)) flips++;
            }else {
                if(a&1) flips++;

                if(b&1) flips++;

                // flips += (a&1) + (b&1) ;
             }

             a >>= 1;
             b >>= 1;
             c >>= 1;
        }

        return flips;
        
    }
};

// using some more concepts

class Solution {
public:
    int minFlips(int a, int b, int c) {

        return __builtin_popcount(((a|b)^c)) +  __builtin_popcount(((a|b)^c) & (a&b)) ;
        
    }
};