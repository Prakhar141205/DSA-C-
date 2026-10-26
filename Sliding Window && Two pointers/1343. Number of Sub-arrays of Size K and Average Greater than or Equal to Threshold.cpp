class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int n = arr.size();
        vector<int> pre(n, 0);
        pre[0] = arr[0];

        for(int i=1; i<n; i++) {
            pre[i] = pre[i-1] + arr[i];
        }

        int l = 0;
        int r = k-1 ;
        int ans = 0;
        while(r < n) {

            int sum = pre[r] - pre[l] + arr[l] ;
            
            double avg = sum / (1.0 * k) ;
            if(avg >= threshold) {
                ans++;
            }
            l++;
            r++;
        }

        return ans;
    }
};