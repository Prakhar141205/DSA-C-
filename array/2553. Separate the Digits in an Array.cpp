class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> ans ;
        
        for( auto &it : nums ){
            
            string tmp = to_string(it);
            
            for( auto &s : tmp ) ans.push_back(s-'0');
            
        }
        
        return ans ;
    }
};

class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
       vector<int>ans;
       for(int i = nums.size() - 1; i>=0; i--){
        while(nums[i] > 0){
            int digit = nums[i] % 10;
            nums[i] = nums[i] / 10;
            ans.push_back(digit);
        }
       } 
       reverse(ans.begin(), ans.end());
       return ans;
    }
};