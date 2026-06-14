class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st;

        // insert all the elements to the set

        for(int i=0; i<nums.size(); i++){
            st.insert(nums[i]);
        }
       
       int largest = 0;
       for(auto x: st){
        // check prev element exists or not
        if(st.find(x-1) == st.end()){ //  prev element not exist
            // initialize the cnt var

            int cnt=1;
            while(st.find(x+1) != st.end()){

                x++;
                cnt++;
            }

            largest = max(largest, cnt);
        }
       }

       return largest;
    }
};