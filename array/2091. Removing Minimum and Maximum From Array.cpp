class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        if(n == 1 or n == 2)  return n ;
        int maxI = -1, maxEle = INT_MIN;
        int minI = -1, minEle = INT_MAX;
        for(int i=0; i<n; i++) {
            
            if(nums[i] > maxEle) {
                maxI = i;
                maxEle = nums[i];
            }

            if(nums[i] < minEle) {
                minI = i;
                minEle = nums[i];
            }
        }

        if(minI > maxI) swap(minI, maxI);

        int fromFront = maxI+1;
        int fromBack  = n - minI ;
        int fromBoth  = (minI + 1) + (n - maxI);

        return min({fromFront, fromBack, fromBoth});
    
    }
};