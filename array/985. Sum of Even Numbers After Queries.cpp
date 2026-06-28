class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {

        int n = nums.size();
        int m = queries.size();
        int evenSum = 0;
        for(int& e : nums){
            if(! (e & 1) ) evenSum += e;
        }

        vector<int> res;
        for(int i=0; i<m; i++){
            int val = queries[i][0];
            int idx = queries[i][1];
            
            if(nums[idx] & 1){
                nums[idx] += val;
                if(!(nums[idx] & 1)) evenSum += nums[idx];
            } else {
                int temp = nums[idx];
                evenSum -= temp;
                nums[idx] += val;

                if(!(nums[idx] & 1)) evenSum = evenSum + nums[idx];

            }


            res.push_back(evenSum);

           

            
        }
        
        return res;
    }
};