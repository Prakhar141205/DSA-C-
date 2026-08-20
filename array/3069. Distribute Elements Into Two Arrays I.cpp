class Solution {
public:
    vector<int> resultArray(vector<int>& nums) { 
        int n = nums.size();

        vector<int> arr1;
        vector<int> arr2;

        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        
        int i1 = 0, i2 = 0 ;
        for(int i=2; i<n; i++) {

            if(arr1.back() > arr2.back()) {
                arr1.push_back(nums[i]);
            }else {
                arr2.push_back(nums[i]);
            }
        }
        i1 = 0, i2 = 0;
        int j=0;

        while(i1 < arr1.size()) {
            nums[j++] = arr1[i1++];
        }
        while(i2 < arr2.size()) {
            nums[j++] = arr2[i2++];
        }

        return nums;
    }
};2