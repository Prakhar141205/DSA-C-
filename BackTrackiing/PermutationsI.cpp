nclass Solution {
public:
    vector<vector<int>> ans ;
    unordered_set<int> st ;
    void findPermutations(vector<int>& temp, vector<int>& nums) {
        if(temp.size() == nums.size()) {
            ans.push_back(temp);
            return;
        }


        for(int i=0; i<nums.size(); i++) {
            if(st.find(nums[i]) == st.end()){

                temp.push_back(nums[i]);
                st.insert(nums[i]);

                findPermutations(temp, nums);

                temp.pop_back();
                st.erase(nums[i]);
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> temp;
        findPermutations(temp, nums);

        return ans;
        
    }
};

// Approach 2 

class Solution {
public:
    vector<vector<int>> ans ;
    void findPermutations(int index, vector<int>& nums) {
        if(index == nums.size()) {
            ans.push_back(nums);
            return;
        }

        for(int i=index; i<nums.size(); i++) {
            swap(nums[index], nums[i]);
            findPermutations(index+1, nums);
            swap(nums[index], nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        findPermutations(0, nums);
        return ans;
    }
};  