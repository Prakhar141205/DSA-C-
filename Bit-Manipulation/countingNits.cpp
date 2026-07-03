class Solution {
public:
    /* 
     number of 1's bit in binary representation 
     an even number and its half has same number of 1 bits
     while an odd number has bits more than one half of the number
    */
    vector<int> countBits(int n) {

        vector<int> res(n+1, 0);

        for(int i=0; i<n+1; i++) {

            if(i & 1) { // odd
                res[i] = res[i/2] + 1;

            }else {
                res[i] = res[i/2];
            }
        }
        return res;
    }
};