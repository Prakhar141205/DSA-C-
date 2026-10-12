class Solution {
public:
    const int mod = 1e9+7;
    int maxSum(vector<int>& nums, int k) {
        vector<int> count(32, 0); // stores the cnt of ones bit in each position

        // fill the cnt array 
        for(int num : nums ) {

            for(int b=0; b<32; b++) {

                if(num & (1 << b)) { // bth bit of num is one
                    count[b]++;
                }
            }
        }
        
        int res = 0;

        while(k--) {
            long long curr = 0;
            for(int b=0; b <32; b++) {
                if(count[b] > 0) {
                    count[b]--;
                    curr = (curr | (1 << b)) ;
                }
            }

            res = (res + (curr*curr)) % mod;
        }

        return res;
    }
};