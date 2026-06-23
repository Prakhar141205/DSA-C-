class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int closestSum = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < n - 2; i++) {
            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int currentSum = nums[i] + nums[j] + nums[k];

                // Update closest sum if this one is better
                if (abs(currentSum - target) < abs(closestSum - target)) {
                    closestSum = currentSum;
                }

                // Move pointers based on comparison to target
                if (currentSum == target) {
                    return target; // can't get closer than exact match
                } else if (currentSum < target) {
                    j++; // need a bigger sum, move left pointer right
                } else {
                    k--; // need a smaller sum, move right pointer left
                }
            }
        }

        return closestSum;
    }
};