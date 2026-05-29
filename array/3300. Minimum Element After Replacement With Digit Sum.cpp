class Solution {
public:
    int minElement(vector<int>& nums) {
        int res = 36;
        for (int i = 0; i < nums.size(); i++)
            res = min(res, integrate(nums[i]) - integrate(nums[i] - 1));
        return res;
    }

    int integrate(int n) {
        int sum = (n * (n + 1)) >> 1;
        sum -= 9 * (block(n, 10) + block(n, 100) + block(n, 1000) +
                    block(n, 10000));
        return sum;
    }

    int block(int n, int k) {
        auto [q, r] = div(n, k);
        return k * ((q * (q - 1)) >> 1) + q * (r + 1);
    }
};

class Solution {
public:
    // TC (logN)
    // int sumOfDigits(int n){
    //     int sum = 0;
    //     while(n){
    //         sum += n % 10;
    //         n /= 10;
    //     }
    //     return sum;
    // }
    
    int sumOfDigit(int n){
        return n - 9*((n/10) + (n/100) + (n/1000) + (n/10000));
    }
    int minElement(vector<int>& nums) {
        int ans = INT_MAX;
        int n = nums.size();

        for(int i=0; i<n; i++){
            ans = min(ans, sumOfDigit(nums[i]));
        }
        return ans;
    }
};