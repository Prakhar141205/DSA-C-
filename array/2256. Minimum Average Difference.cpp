class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {

        int n = nums.size();

        long long total_sum = nums[0];

        for(int i=1; i<n; i++) {

            total_sum += nums[i];
            
        }

        long long left_sum = 0;
        int min_diff = 1e9;
        int index=-1;
        for(int i=0; i<n; i++){
            left_sum += nums[i];

            int left_avg = left_sum/(i+1);

            int right_avg = (i == n-1) ? 0 : (total_sum - left_sum)/(n-i-1);

            int avg_diff = abs(left_avg - right_avg) ;

            if(min_diff > avg_diff){
                min_diff = avg_diff;
                index = i;
            }

        }
        return index;
    }
};