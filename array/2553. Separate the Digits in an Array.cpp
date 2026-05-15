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

class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> result;
        for(int num:nums){
            vector<int> digits;
            while(num>0){
            digits.push_back(num%10);
            num/=10;
        }
        reverse(digits.begin(), digits.end());
        result.insert(result.end(), digits.begin(), digits.end());
    }
    return result;
    }
};