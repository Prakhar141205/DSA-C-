class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        queue<int> qPos;
        queue<int> qNeg;

        for(int& x : nums) {
            if(x < 0) qNeg.push(x);
            else qPos.push(x);
        }

        vector<int> ans(n, 0);
        for(int i=0; i<n; i++) {
            if(!(i & 1)) {
                ans[i] = qPos.front();
                qPos.pop();
            }else {
                ans[i] = qNeg.front();
                qNeg.pop();
            }
        }
        return ans;
    }   
};

// using two pointer approach 
// first pointer = odd index
// second pointer = even index

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int e = 0, o = 1;
        int n = nums.size();
        vector<int> res(n);
        int i=0;
        while(i < n) {
            int ele = nums[i++];
            if(ele > 0) {
                res[e] = ele;
                e += 2;
            }else {
                res[o] = ele;
                o += 2;
            }
        }

        return res;
    }   
}; 