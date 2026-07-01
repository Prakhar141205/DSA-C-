class Solution {
public:
    int singleNumber(vector<int>& nums) {

        // APproach 1 => use map <element, freq >
        // Approach 2 => sort than track using both the neighbours

        // int ==> 32 bit

        int res = 0;
        for(int k=0; k<= 31; k++) {

            int temp = (1 << k) ; 
            int countZeros = 0, countOnes = 0;

            for(int& num : nums) {

                if((temp & num)) {
                    countOnes++;
                }else {
                    countZeros++;
                }
            }

            if (countOnes % 3 == 1 ) 
                    res |= temp ;

        }


        return res;
    }
};