class Solution {
public:
    int n;
    int t[10001];
    bool solve(vector<int>& nums, int idx) {
        if(idx == n-1) return true;
        if(idx >= n) return false;
        if(t[idx] != -1) return t[idx];

        for(int i=1; i<=nums[idx]; i++) {

            if(solve(nums, idx + i )) return true;
        }

        return t[idx] = false;
    }
    bool canJump(vector<int>& nums) {
        n = nums.size();
        memset(t, -1, sizeof(t));
        return solve(nums, 0);
    }
};

// Bottom Up Approach
class Solution {
public:
    int n;
    
    bool canJump(vector<int>& nums) {
        n = nums.size();
        vector<int> t(n, 0);

        t[0] = 1 ;

        for(int i=1; i<n; i++) {

            for(int j=i-1; j >= 0; j--) {

                if(t[j] && j + nums[j] >= i) {
                    t[i] = true;
                    break;
                }
            }
        }
        return t[n-1];
    }
};

// Smart Approach

class Solution {
public:
    int n;
    
    bool canJump(vector<int>& nums) {
        n = nums.size();

        int maxReachable = 0;

        for(int i=0; i<n; i++) {
            if(i > maxReachable) return false;

            maxReachable = max(maxReachable, i + nums[i]) ;
        }

        return true ;
    }
};