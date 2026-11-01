class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        int i=0, j=n-1;
        for(int i=0; i<n; i++) {
            if(nums[i] < 0) nums[i] = -1*nums[i];
        }

        sort(nums.begin(), nums.end());

        long long sum = 0;
        while(i < j) {
            sum += (nums[j]*nums[j]);
            j--;
            sum -= (nums[i] * nums[i] );
            i++;
        }

        if(i == j) {
            sum += (nums[i] * nums[i]);
        }
        return sum;
    }
};

// Alternate approach 
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        // pull all the minimum values at the odd index
        // than solve the entire questions
        int n = nums.size();
        for(int i=0; i<n; i++) {
            if(nums[i] < 0) nums[i] = -1*nums[i];
        }

        sort(begin(nums), end(nums));

        int i=0, j=n-1;

        int k = 0;
        long long sum = 0;
        while(k < n) {
            if(k&1) {
                sum -= (1L*nums[i]*nums[i]) ;
                i++;
            }else {
                sum += (1L*nums[j] * nums[j]);
                j--;
            }
            k++;
        }

        return sum;
    }
};