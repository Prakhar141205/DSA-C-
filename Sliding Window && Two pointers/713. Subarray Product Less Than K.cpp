class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        // this is must condition
        if(k <= 1) return 0;
        int cnt = 0;

        int l = 0, r = 0;
        int prod = 1;
        // sliding window start

        while (r < n) {
            prod *= nums[r];

            while (l < r && prod >= k) { // decrease the window size;
                prod /= nums[l];
                l++;
            }

            if(prod < k)
                cnt += (r - l + 1); // in valid window we get no of subarrays =
                                    // length of window

            r++;
        }
        return cnt;
    }
};