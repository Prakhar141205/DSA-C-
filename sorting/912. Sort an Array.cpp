/*
- Use Counting Sort when the input values lie within a bounded range.
-nums[i] belongs tp [-5 * 10 ^ 4 , 5 * 10 ^ 4]
- arr[nums[i] + 50000] handles negative numbers by shifting them to non-negative indices.
- Reconstruct the sorted array by traversing the frequency array and repeating each value according to its frequency.
- Time: O(n + k), Space: O(k), where k = 100001 (range size).
- Counting Sort avoids comparison-based sorting, achieving O(n) time for a fixed range.

*/

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int arr[100001] = {0};

        for(int i=0; i< nums.size(); i++) {
            arr[nums[i]+50000] += 1;
        }
        vector<int> ans;
        for(int i=0; i < 100001; i++) {

            while(arr[i]--) {
                ans.push_back(i - 50000);
            }
        }

        return ans;
        }
};