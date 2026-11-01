class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        // int n = banned.size();

        unordered_set<int> st(banned.begin(), banned.end());
        int currSum=0;
        int num=1, ans=0;

       for(int num=1; num <= n; num++) {
            if(st.find(num) == st.end()) {;
                currSum += num ;
                if(currSum > maxSum ) break;
                

                ans++;
            }

        }
        return ans;
    }
};