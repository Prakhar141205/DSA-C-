class Solution {
    vector<int> getNegative(vector<int>& nums, int k){
        int n = nums.size();
        vector<int> res;
        int l=0, r=0;
        queue<int> q;
        while(r < n){
            // negative than push in the queue
            if(nums[r] < 0) q.push(nums[i]);

            if(r - l + 1 == k){
                if(!q.empty()) res.push_back(q.front());
                else res.push_back(0);

                if(nums[l] < 0 && !q.empty()) q.pop();

                l++;
            }
            r++;

        }

        return res;
    }
};