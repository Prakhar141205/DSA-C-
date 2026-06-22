class Solution {
public:
    int bSearch(int target_idx, int k, vector<int> nums, vector<long> prefix){

        int l = 0, r = target_idx;

        int best_idx = target_idx;

        while( l <= r){
            int mid = l + (r-l)/2;

            long count = target_idx - mid + 1 ;

            long currSum = count * nums[target_idx];

            long originalSum = prefix[target_idx] - prefix[mid] + nums[mid];
            int ops = currSum - originalSum;
            if(ops > k){
                l = mid+1;
            }else{
                best_idx = mid;
                r = mid-1;
            }
        }

        return target_idx - best_idx + 1;
    }
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<long> prefix(n, 0);
        prefix[0] = nums[0];

        for(int i=1; i<n; i++){
            prefix[i] = prefix[i-1] + nums[i];
        }

        int result=0;
        for(int target_idx=0; target_idx < n; target_idx++){
            result = max(result, bSearch(target_idx, k, nums, prefix));
        }
        
        return result;
    }
};

// using Sliding Window

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        long currSum = 0;

        int result=0;
        int l=0;
        
        for(int r=0; r < n; r++){ 

            long target = nums[r];
            currSum += target;

            
            while(1LL * ((r-l+1) * target) - currSum > 1LL*k){
                currSum -= nums[l];
                l++;
                // ops = (r - l + 1) * nums[r] - currSum;
            }
            result = max(result, r - l + 1);
        }
        
        return result;
    }
};

// Sliding window optimized

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        // using sliding window//
        // first sort entire array

        sort(nums.begin(), nums.end());

        long long currSum = 0;
        int result = 0;
        int l = 0; // left pointer

        long long ops = 0;
        int frequency = 0;

        for (int r = 0; r < nums.size(); r++) { // right pointer
            currSum += nums[r];
            long long windSum = (long long)(r - l + 1) * nums[r];

            ops = windSum - currSum;

            if (ops > k) { // means that window is not perfect so sink window
                           // for moving l by 1
                currSum -= nums[l];
                l++;
                ops = (long long)(r - l + 1) * nums[r] - currSum;
            } else { // if valid then l is at its place and keep runnig loop in
                     // which r is keep moving by 1 through loop
                frequency =  r - l + 1; // eg. if window size is n means its max frequency is n
                result = max(result, frequency);
            }
        }
        return result;
    }
};