class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        
        int n = nums.size() ;
        unordered_set<int> xorPair;

        for(int i=0; i<n; i++) {
            for(int j=i; j<n; j++) {

                xorPair.insert(nums[i] ^ nums[j]) ;
            }
        }
        unordered_set<int> ans;

        for(const int& c : xorPair) {
            for(int i=0; i<n; i++) {
                ans.insert(c ^ nums[i]) ;
            }
        }

        return ans.size();
    }
};

// using bool vector 