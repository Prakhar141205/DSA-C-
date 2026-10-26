class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {
        int n = arr.size();

        int l=0, r= n-1;

        while(l < r) {
            int m = l + (r-l) / 2;  

            bool isEven = ((r-m) % 2 == 0) ? true : false ;

            if(arr[m] == arr[m+1]) {
                if(isEven ) {
                    l = m + 2;
                }else {
                    r = m  - 1;
                }
            }else {

                if(isEven) {
                    r = m;
                }else {
                    l = m + 1;
                }
            }
        } 
        return arr[r];
    }
};