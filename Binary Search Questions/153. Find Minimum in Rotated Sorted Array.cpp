class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();

        int l =0, r = n-1;
 
        while(l < r){ // not l <= r => stucked in loop
            int mid = l + (r-l)/2;

            if(nums[mid] > nums[r]){
                l = mid + 1; // nums[m] is greater means it can never be ans
            }else {
                r = mid; // as nums[m] is smaller than it could be an answer
            }
        }
        
        return nums[l]; // or nums[r]  as l == r the loops breaks at the minimum element;
    }
};