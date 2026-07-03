class Solution {
public:
    int findCntOnes(int a){
        int cnt=0;

        while(a) {
            if((a & 1) == 1) cnt++;

            a >>= 1;
        }

        return cnt;
    }
    vector<int> sortByBits(vector<int>& arr) {

        // custom comparator that sorts on the basis of number of 1 bits
        sort(arr.begin(), arr.end(), [&] (int& a, int& b) {
            int cntOnesA = findCntOnes(a); // __builtin_popcount(a);
            int cntOnesB = findCntOnes(b);

            if(cntOnesB == cntOnesA) return a < b ;
            return cntOnesA < cntOnesB;
        });

        return arr;
        
    }
};