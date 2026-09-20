class Solution {
public:
    typedef long long ll ;
    long long maxValue(vector<int>& nums) {
        int n = nums.size();
        ll original_pulse = 0;
        for(int i=0; i<n; i++) {
            original_pulse += (i&1) ? (-1*nums[i]) : (nums[i]) ;
        }

        cout << "Original Pulse: " << original_pulse << "\n";
        vector<ll> A(n);
        for(int i=0; i<n; i++) {
            ll sign = (i&1) ? -1 : 1 ;
            A[i] = -2*sign*nums[i];
        }

        vector<ll> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + A[i];
        }

        ll max_delta = 0 ;
        ll mep = pref[0];
        ll mop = 1e18 ;

        for(int k = 1; k <=n; k++) {
            if(k%2) {
                if(mop != 1e18) {
                     max_delta = max(max_delta, pref[k] - mop);
                }
                mop = min(mop, pref[k]);
            }else {
                 max_delta = max(max_delta, pref[k] - mep);
                mep = min(mep, pref[k]);
        }
        }
         return original_pulse + max_delta;
    }
};©leetcode