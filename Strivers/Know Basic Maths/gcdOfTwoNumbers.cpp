class Solution {
public:
    typedef long long ll;
    int gcd(int x, int y) {    

        while(x && y) {
            if(x > y) {
                x = x % y ;
            }else {
                y = y % x ;
            }
        }

        return x == 0 ? y : x  ;
    }
};


int main() {

    Solution o1 ;

    cout << o1.gcd(2, 5) ;
    return 0;
}