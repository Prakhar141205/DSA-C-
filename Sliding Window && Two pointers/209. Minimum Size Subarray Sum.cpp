// o(N) approach
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l=0, r=0, n = nums.size();

        int currSum = 0, minLen = 1e9;
        while(r < n){
            currSum += nums[r];

            while(currSum >= target){
                minLen = min(minLen, r-l+1);
                currSum -= nums[l];
                l++;
            }
            r++;
        }
        return minLen == 1e9 ? 0 : minLen;
    }
};

// o(nlogn) prefixSum + binary search