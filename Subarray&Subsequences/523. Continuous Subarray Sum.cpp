class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // using simple modulo concept
        //  the concept is that:
        //  if we have (x % k == y) than (x + multiple of k) % k also equals to the y

        unordered_map<int, int> mp; // remainder, index
        if(nums.size() == 1 && nums[0] == 0) return false; 

        mp[0] = -1;
        int sum = 0;
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];

            int rem = sum%k;

            if(mp.find(rem) != mp.end()){
                if(i - mp[rem]  >= 2) return true;
            }else{
                mp[rem] = i;
            }

            


        }

        return false;
    }
};