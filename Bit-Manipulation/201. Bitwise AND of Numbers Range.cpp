class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shiftCnt = 0;
        // 
        while(left != right) {
            // get the longest common prefix of the two binary numbers
            left = (left >> 1);
            right = (right >> 1);
            shiftCnt++;
        }

        return (left << shiftCnt);
        
    }
};

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {

        while(left < right) {
            right &= (right-1);
        }

        return right;
        
    }
};