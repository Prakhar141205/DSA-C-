class Solution {
public:
    map<string,int> dp;
    string binary(int n){
        string temp = "";
        int x = 1;
        while(n){
            if(n & 1){
                temp += '1';
            } else {
                temp += '0';
            }
            n>>=1;
        }
        return temp;
    }
    int solve(string &str){
        int n =str.length();
        int cnt = 0;
        int ans = 0;
        for(int i=n-1;i>=0;i--){
            if(str[i] == '0')
            continue;
            int num = 1<<i;
            cout<<num<<endl;
            if(cnt%2 == 0){
                ans+=2*num-1;
                cnt++;
            } else {
                ans-=2*num-1;
                cnt++;
            }
        }
        return ans;
    }
    int minimumOneBitOperations(int n) {
        string str = binary(n);
        return solve(str);
        return 0;
    }
};


class Solution {
public:
    int minimumOneBitOperations(int n) {
        if(n == 0) return 0;

        vector<long long> F(31, 0);

        F[0] = 1;

        for(int i=1; i <=30; i++) {
            F[i] = 2 * F[i-1] + 1;
        }

        int res = 0;
        int sign = 1;

        for(int i=30; i>=0; i--) {

            int ith_bit = ((n >> i) & 1); // returns only 0 and 1
            // int ith_bit = ((1 << i) & n);

            if(ith_bit == 0) {
                continue;
            }
            
            if(sign > 0) {
                res += F[i];
            }else {
                res -= F[i];
            }

            sign *= (-1);
        }

        return res;
    }
};