class Solution {
public:
    void nextPermutation(vector<int>& nums) {

        int index = -1; // index at which slope drops
        int n = nums.size();

        for(int i=n-1; i>=1; i--){
            if(nums[i-1] < nums[i]){
                index = i-1;
                break;
            }
        }
        // swap with the next greater than nums[index] from last
        if(index != -1){

            int swap_index = index;

            for(int i=n-1; i >= index+1 ; i--){
                if(nums[i] > nums[index]) {swap_index = i; break;}
            }

            swap(nums[index], nums[swap_index]);
            
            reverse(nums.begin() + index+1, nums.end());
        }else {
            reverse(nums.begin(), nums.end());
        }


        return;
    }
};