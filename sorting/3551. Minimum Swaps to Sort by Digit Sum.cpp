class Solution {
public:
    int getDigitSum(int n) {
        int ans = 0;

        while(n) {
            ans += (n%10);
            n /= 10;
        }
        return ans;
    }
    int minSwaps(vector<int>& nums) {
        int n= nums.size();

        vector<int> afterSorted = nums;

        sort(begin(afterSorted), end(afterSorted), [&](int num1, int num2) {
            int sum1 = getDigitSum(num1);
            int sum2 = getDigitSum(num2);

            if(sum1 != sum2) return sum1 <  sum2;

            return num1 < num2 ;
        });


        unordered_map<int, int> valToIdx;
        for(int i=0; i<n; i++) {
            valToIdx[nums[i]] = i ; 
        }

        int cnt = 0;
        for(int i=0; i<n; i++) {
            if(nums[i] != valToIdx[i] ) {
                int expectedVal = afterSorted[i];
                int currVal = nums[i];

                if(expectedVal == currVal ) continue;
                else {
                    int idx =  valToIdx[expectedVal];
                    nums[i] = expectedVal;
                    nums[idx] = currVal;

                    valToIdx[expectedVal] = i;
                    valToIdx[currVal] = idx;
                    cnt  += 1;
                }
                
            }
        }

        return cnt;
    }
};