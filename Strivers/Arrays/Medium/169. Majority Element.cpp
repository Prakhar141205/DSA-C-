// Majority Element I
// Algorithm: Boyer-Moore Voting Algorithm:

/*
Logic: Assuming that the majority element always exists in the array, we can use the Boyer-Moore Voting Algorithm to find it in linear time and constant space. The idea is to maintain a count of the current candidate for the majority element. If the count drops to zero, we select a new candidate. At the end of the iteration, the candidate will be the majority element.

*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;
        int maj = NULL;

        for(int i=0; i<n; i++) {
            if(nums[i] == maj) {
                cnt++;
            }else if(cnt == 0) {
                maj = nums[i];
                cnt = 1;
            }else {
                cnt--;
            }
        }
        
        return maj;
    }
};