class Solution {
public:
    typedef long long ll;

    long long minimumDifference(vector<int>& nums) {
        int N = nums.size();
        int n = N/3;

        vector<ll> leftMinSum(N, 0);
        vector<ll> rightMaxSum(N, 0);

        priority_queue<int> maxHeap;
        ll leftSum = 0;

        for(int i=0; i<2*n; i++) {
            leftSum += nums[i];
            maxHeap.push(nums[i]);

            if(maxHeap.size() > n ) {
                leftSum -= maxHeap.top();
                maxHeap.pop();

            }

            leftMinSum[i] = leftSum;

        }
        priority_queue<int, vector<int>, greater<int>> minHeap;
        ll rightSum = 0;

        for(int i=N-1; i>=n; i--) {
            rightSum += nums[i];
            minHeap.push(nums[i]);

            if(minHeap.size() > n ) {
                rightSum -= minHeap.top();
                minHeap.pop();

            }

            rightMaxSum[i] = rightSum;
        }

        ll res = LLONG_MAX;
        for(int i=n-1; i<=2*n-1; i++) {
            res = min(res, (leftMinSum[i] - rightMaxSum[i+1]));
        }

        return res;
    }

};