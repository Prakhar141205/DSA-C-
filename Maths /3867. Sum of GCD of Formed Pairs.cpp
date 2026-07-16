class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixMax(n, 0);

        prefixMax[0] = nums[0];
        for(int i=1; i<n; i++) {
            prefixMax[i] = max(prefixMax[i-1], nums[i]);
        }       

        vector<int> prefixGcd(n);
        

        for(int i=0; i<n; i++) {
            prefixGcd[i] = __gcd(prefixMax[i], nums[i]);
        }

        for(int x : prefixGcd) cout << x << " ";
        sort(prefixGcd.begin(), prefixGcd.end());
        int l=0, r=n-1;
        long long ans = 0;
        while(l < r) {
            ans += __gcd(prefixGcd[l], prefixGcd[r]);
            l++;
            r--;
        }
        return ans;
    }
};