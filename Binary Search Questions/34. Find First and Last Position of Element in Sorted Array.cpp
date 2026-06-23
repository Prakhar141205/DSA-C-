class Solution {
public:
    int findLeftMax(vector<int> nums, int target, int n){
        int l=0, r = n-1;
        int leftIndex = -1;
        while( l <= r){
            
            int mid = l + (r-l)/2;
            if(nums[mid] < target){
                l = mid+1;
            }else if(nums[mid] > target){
                r = mid - 1 ;
            }else {

                leftIndex = mid; // store the mid index
                r = mid-1;        // look for more left
            
            }

        }

        return leftIndex;
    }
    int findRightMax(vector<int> nums, int target, int n){
        int l=0, r = n-1;
        int lastIndex = -1;
        while( l <= r){
            
            int mid = l + (r-l)/2;

            if(nums[mid] < target){
                l = mid+1;
            }else if(nums[mid] > target){
                r = mid - 1 ;
            }else {

                lastIndex = mid; // store the mid index
                l = mid + 1;        // look for more left
            
            }

        }

        return lastIndex;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();

        int firstIndex = findLeftMax(nums, target, n);

        int lastIndex = findRightMax(nums, target, n);

        
        return {firstIndex, lastIndex};
        
    }
};