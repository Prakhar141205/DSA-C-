class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();
        vector<int> lessP;
        vector<int> moreP;
        int cnt=0;
        for(int i=0; i<n; i++){
            int x = nums[i];
            if(x < pivot) lessP.push_back(x);
            else if(x > pivot) moreP.push_back(x);
            else cnt++;
        }

        int k=0;
        for(int i=0; i<lessP.size(); i++){
            nums[k++] = lessP[i];
        }

        for(int i=0; i<cnt; i++){
            nums[k++] = pivot;
        }
        for(int i=0; i<moreP.size(); i++){
            nums[k++] = moreP[i];
        }

        return nums;
    }
};

auto init = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();
class Solution {
public:
    vector<int> pivotArray(const vector<int>& nums, int pivot) {
        const int n = ssize(nums);
        int l = 0, r = n - 1;
        vector<int> ans(n);

        for(int i = 0, j = n-1; i < n,j>=0; ++i,--j){
            if(nums[i] < pivot) ans[l++] = nums[i];
            if(nums[j] > pivot) ans[r--] = nums[j];
        }
        while(l <= r){
            ans[l++] = pivot;
        }
        return ans;

    }
};