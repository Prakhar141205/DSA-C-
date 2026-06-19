class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int l = k, r =k;
        
        int max_score = nums[k];
        int curr_min = nums[k];
        while(l > 0 || r < n-1){
            
            int leftVal = l > 0 ? nums[l-1] : 0;
            int rightVal = r < n-1 ? nums[r+1]: 0;
            // start from the give index and take steps greedily towrds the maximum element

            if(leftVal > rightVal){
                l--;
                curr_min = min(leftVal, curr_min);
            } else{
                r++;
                curr_min = min(rightVal, curr_min);
            }

            int curr_len = r - l + 1 ;
            max_score = max(curr_min * curr_len, max_score);    
                    
        } 

        return max_score;
    }
};