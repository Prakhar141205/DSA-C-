class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n  = nums.size();
        vector<int> m(n);
        m[n-1] = nums[n-1];

        for(int i=n-2; i>=0; i--) {
            m[i] = min(m[i+1], nums[i]);
        }

        int leftMax = INT_MIN;

        int i=0;

        while(i < n) {
            leftMax = max(leftMax, nums[i]) ;
            int Score = leftMax - m[i];

            if(Score <= k) {
                return i ;
            }

            i++;
        }
        
        return -1 ;
    }
};