class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int n = nums.size();
        if(n % k != 0) return false;

        map<int, int> mp;
        for(int& x : nums) mp[x]++;

        while(mp.size()) {
            auto curr = mp.begin()->first;

            for(int i=0; i<k; i++) {

                if(mp.find(curr+i) == mp.end()) {
                    return false;
                }else {
                    mp[curr+i]--;
                    if(mp[curr+i] == 0) {
                        mp.erase(curr+i);
                    }
                }
            }
        }

        return mp.size() == 0;
    }
};