class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k= k%nums.size();
        reverse(nums.begin(),nums.end());
        reverse(nums.begin(),nums.begin()+k);
        reverse(nums.begin()+k,nums.end());
        
        }
    
};

// TC O(N*k)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1) return;
        while(k--){
            int startElement = nums[0];

            for(int i=n-1; i>=0; i--){
                if (i == 0) nums[i+1] = startElement;
                else nums[(i+1)%n] = nums[i];
            }
            
        }
        
    }
};