class Solution {
public:

    int findPivot(vector<int> nums, int target){
        int l = 0;
        int r = nums.size()-1;

        while(l < r){
            int m = l + (r - l)/2;

            if(nums[m] > nums[r]) l = m + 1;
            else r = m; // in this case mid can also be the answer

            
        }
        return l;
    }

    int binarySearch(vector<int> &nums, int l, int r, int target){

        while(l <= r){
            int m = l + (r - l)/2;

            if(nums[m] == target) return m;
            else if (nums[m] > target) r = m-1; // in this case mid can also be the answer
            else l = m + 1;
            
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n == 0) return -1;
        int l = 0;
        int r = n-1;

        int pivot = findPivot(nums, target);

        if(pivot > 0 && target >= nums[0] && target <= nums[pivot-1])
            return binarySearch(nums, l, pivot-1, target);
        else 
            return binarySearch(nums, pivot, r, target);
    }
};

// Approach 2

class Solution {
public:

    
    
    int search(vector<int>& nums, int target) {
        
        if(nums.size() == 0) return -1;
        
        int r = nums.size()-1, l=0;

        while(l <= r){
            int m = l + (r-l)/2;

            if(nums[m] == target) return m;

            if(nums[l] <= nums[m]){
                // check where the target lies
                if(target < nums[m] && target >= nums[l]) r = m - 1;
                else l = m + 1;
            }else {
                if(target > nums[m] && target <= nums[r]) l = m +1;
                else r = m-1;
            }
        }
        return -1;
    }
};

// Solution 3
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n==0)
        {
            return -1;
        }
        if(nums[0]==target)
        {
            return 0;
        }
        int i=1;
        while(i<n && nums[i]>nums[i-1])
        {
            if(nums[i]==target)
            {
                return i;
            }
            i++;
        }
        int l = i;
        int r = n-1;
        while(l<=r)
        {
            int mid = (l+r)/2;
            if(nums[mid]==target)
            {
                return mid;
            }
            if(nums[mid]>target)
            {
                r = mid-1;
            }
            else
            {
                l = mid+1;
            }
        }


        return -1;
    }
};