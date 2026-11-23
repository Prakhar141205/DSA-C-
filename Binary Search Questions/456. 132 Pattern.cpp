class Solution {
public:
    bool find132pattern(vector<int>& nums) {

        int n = nums.size();

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                for(int k = j + 1; k < n; k++) {

                    if(nums[i] < nums[k] &&
                       nums[k] < nums[j]) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

class Solution {
public:
    bool find132pattern(vector<int>& nums) {

        int n = nums.size();

        // Store the minimum element from index 0 to i.
        vector<int> prefixMin(n);

        prefixMin[0] = nums[0];

        for(int i = 1; i < n; i++) {
            prefixMin[i] = min(prefixMin[i-1], nums[i]);
        }

        // Fix j as the middle index (3).
        for(int j = 1; j < n - 1; j++) {

            // Smallest element before j (1).
            int one = prefixMin[j - 1];

            // Fix k as the last index (2).
            for(int k = j + 1; k < n; k++) {

                if(one < nums[k] && nums[k] < nums[j]) {
                    return true;
                }
            }
        }

        return false;
    }
};

class Solution {
public:
    bool find132pattern(vector<int>& nums) {

        int n = nums.size();

        // Stack stores potential 3 values.
        stack<int> st;

        // Stores the best possible 2 value.
        int third = INT_MIN;

        // Traverse from right to left.
        for(int i = n - 1; i >= 0; i--) {

            // Current element can act as 1.
            // If it is smaller than our selected 2,
            // then a valid 132 pattern exists.
            if(nums[i] < third) {
                return true;
            }

            // Find a 3 that is greater than the current
            // element and update the best possible 2.
            while(!st.empty() && nums[i] > st.top()) {

                // The popped element acts as 2.
                third = st.top();
                st.pop();
            }

            // Current element can be a potential 3.
            st.push(nums[i]);
        }

        return false;
    }
};