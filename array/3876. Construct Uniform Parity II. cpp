class Solution {
public:
    bool uniformArray(vector<int>& nums) {
        int m = *min_element(nums.begin(), nums.end()) ;

        if(m & 1) return true;// if min is odd than we can convert all even to odd
        // all nums2 will be odd

        for(int& n : nums) if(n & 1) return false ; // check if we can make all even in num2  
        return  true; // all num2 will be even
        
    }
};