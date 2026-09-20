class Solution {

    public :
        int cntAllDigits(int n) {
            int cnt = 0;

            while(n) {
                cnt++;
                n /= 10 ;
            }
            return cnt;
        }

        int cntAllDigits(int n) {
           
            return (int)(log10(n) + 1);
        }
}


int main() {
    Solution obj1;

    int x = obj.cntAllDigits(123456);

    cout << x << "\n";

    return 0;
}

// mathod 2 

