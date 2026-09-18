class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        int l=0;

        int currSum = 0;
        int ans = INT_MAX;
        int bestMinLen = INT_MAX;
        vector<int> minBestLenTillIdx(n, INT_MAX);


        for(int r=0; r<n; r++) {
            currSum += arr[r];
            while(l < r && currSum > target) {
                currSum -= arr[l++];
            }

            if(currSum == target) {
                int len = (r-l+1);

                if(l > 0 && minBestLenTillIdx[l-1] != INT_MAX) {
                    ans = min(ans, len + minBestLenTillIdx[l-1]);

                }

                bestMinLen = min(bestMinLen, len);
            }
            minBestLenTillIdx[r] = bestMinLen;
        }
        
    return ans == INT_MAX ? -1 : ans;

    }
};