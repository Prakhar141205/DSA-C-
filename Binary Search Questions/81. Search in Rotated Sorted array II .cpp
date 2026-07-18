class Solution {
public:
    int findPivot(vector<int>& nums, int l, int r) {
        while(l < r) {
            while(l < r && nums[l] == nums[l+1]) {
                l++;
            }

            while(r > l && nums[r] == nums[r-1]) {
                r--;
            }

            int mid = l + (r-l)/2;

            if(nums[mid] > nums[r]) {
                l = mid + 1;
            }else {
                r = mid;
            }
            
        }
        return r;
    }
    bool binarySearch(int l, int r, vector<int>& nums, int target) {
        while(l <= r) {
            int mid = l + (r-l)/2 ;
            if(nums[mid] == target) {
                return true;
            }else if (nums[mid] > target) {
                r = mid - 1;
            }else {
                l = mid + 1;
            }
        }
        return false;
    }
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) return (nums[0] == target) ;

        int pivot_idx = findPivot(nums, 0, n-1);

        if(binarySearch(0, pivot_idx, nums, target)) return true;

        return binarySearch(pivot_idx, n-1, nums, target);
        
    }
};