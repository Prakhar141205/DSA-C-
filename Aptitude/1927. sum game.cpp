class Solution {
public:
    bool sumGame(string num) {
        int n = num.length();

        int leftKnownSum = 0;
        int rightKnownSum = 0;

        int leftQnMarkCount = 0 ;
        int rightQnMarkCount = 0;

        for(int i=0; i<n; i++)  {
            if(num[i] == '?') {
                if(i < n/2) {
                    leftQnMarkCount++;
                }else {
                    rightQnMarkCount++;
                }

            }else {
                if(i < n/2 ) {
                    leftKnownSum += num[i] - '0';
                }else {
                    rightKnownSum += num[i] - '0';
                }
            }
            
        }


        int totalQnMarks = leftQnMarkCount + rightQnMarkCount ;

        if(totalQnMarks & 1) return true;

        int left = 2 * leftKnownSum + 9 * leftQnMarkCount ;

        int right = 2 * rightKnownSum + 9 * rightQnMarkCount;

        
        return left == right ? false : true ;
        
    }
};