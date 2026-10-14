class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(num * 9 < sum) return "";
        
        string temp = "";
        int x = num;
        int q = sum / 9 ;
        int m = sum % 9 ;
        while(num && q) {
            temp += "9";

            num--;
            q--;
        }
        if(temp.length() < x)
            temp += to_string(m);

        while(num > 1 ) {
            temp += '0';
            num--;
        }
        return temp;
    }
};

// Using for loop

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(num*9 < sum) return  "";
        int r = sum / 9 ;
        int m  = sum % 9 ;
        string temp  = "";
        for(int i=0; i<num; i++) {
            if(r  > 0) {
                temp += '9';
                r--;
            }else {

            temp += to_string(m);
            m = 0;
            }
        }
        return temp;
    }
};