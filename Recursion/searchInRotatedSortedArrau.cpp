class Solution {
public:
    int helper(vector<int> nums, int st, int end, int target){
        if(st > end) return -1;
        int mid = st + (end-st)/2;

        if(nums[mid] == target) return mid;
        if(nums[st] <= nums[mid]){//left line
                if(nums[st] <= target && nums[mid] >= target){
                    return helper(nums, st, mid-1, target);
                }else{
                    return helper(nums, mid+1, end, target);
                }
        } else{
            if(nums[end] >= target && nums[mid] <= target){
                    return helper(nums,mid+1, end, target);
                }else{
                    return helper(nums, st, mid-1, target);
                }
        }

    }
    int search(vector<int>& nums, int target) {

        return helper(nums, 0, nums.size()-1, target);
    }
};