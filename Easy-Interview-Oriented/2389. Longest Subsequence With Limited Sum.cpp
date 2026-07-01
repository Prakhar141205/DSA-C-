class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        int m = queries.size();

        sort(nums.begin(), nums.end());

        vector<int> ans;
        
        for(int& q : queries) {
            int sum = 0;
            for(int i=0; i<n; i++){
                sum += nums[i];
                if(q < sum ){
                    ans.push_back(i);
                    break;
                }
            }

            if(sum <= q) {
                ans.push_back(n);
            }
        }
        return ans;
    }
};

// using prefix sum + binary search

class Solution {
public:
    int binarySearch(vector<int> nums, int target) {

        int n = nums.size();

        int l=0, r = n-1;
        int cnt = -1;
        while(l <= r) {
            int m = l + (r-l)/2;

            if(target >= nums[m]) {
                cnt = m;
                l = m +1 ;
            }else {
                r = m - 1 ;
            }
        }
        return cnt+1;
    }
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        int m = queries.size();

        sort(nums.begin(), nums.end());

        for(int i=1; i<n; i++) {

            nums[i] += nums[i-1];

        }
        vector<int> ans;
        
        for(int& q : queries) {
            
            int cnt = binarySearch(nums, q) ;

            ans.push_back(cnt);
            
        }

        
        return ans;
    }
};