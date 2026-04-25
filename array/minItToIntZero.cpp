class Solution {
public:
    int makeTheIntegerZero(int n1, int n2) {
        for(int i=1; i<=36; i++){
            long long val = (long long )n1 - (long long) i*n2;

            if(val < 0) return -1;

            if(__builtin_popcountll(val) <= i && i <= val ){
                return i;
            }
        }
        return -1;
    }
};