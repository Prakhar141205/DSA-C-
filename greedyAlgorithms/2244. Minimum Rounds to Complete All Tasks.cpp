class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        unordered_map<int, int> mp;

        for(int& x : tasks) mp[x]++;

        int rnds = 0;

        for(auto [n, cnt] : mp ) {

            if(cnt == 1) return -1;
            if(cnt  % 3 == 0) {
                rnds += cnt/3 ;
            }else  {
                rnds += ((cnt/3) + 1) ;
            }
        }

        return rnds;
    }
};