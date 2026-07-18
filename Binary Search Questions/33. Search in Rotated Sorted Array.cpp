class Solution {
public:
    int findPivot(vector<int>& nums, int l, int r) {
        
        while(l < r) {
            int mid = l + (r-l)/2 ;
            cout << mid << " ";
            if(nums[mid] > nums[r]) {
                l = mid+1;
            }else {
                r = mid ;
            }
        }
        return r;
    }

    int binarySearch(int l, int r, vector<int>& nums, int target) {
        
        while(l <= r) {
            int m = l + (r-l)/2 ;

            if(nums[m] == target) {
                return m;
            }else if(nums[m] > target) {
                r = m - 1;
            }else {
                l = m + 1;
            }
        } 

        return -1;
    }
    int search(vector<int>& nums, int target) {
        int n = nums.size();

        int pivot_idx = findPivot(nums, 0, n-1) ;

        int idx = binarySearch(0, pivot_idx-1, nums, target);

        if(idx != -1) return idx;

        idx = binarySearch(pivot_idx, n-1, nums, target);
        
        return idx;
    }
};