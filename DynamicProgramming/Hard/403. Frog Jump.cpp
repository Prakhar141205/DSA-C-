class Solution {
public:
    int n;
    unordered_map<int, int> mp; // stones, index
    bool solve(vector<int>& stones, int currStoneIndex, int prevJump) {
        if(currStoneIndex == n-1) return true;

        bool result = false;
        for(int nextJump = prevJump-1; nextJump <= prevJump+1; nextJump++) {

            if(nextJump > 0) {
                int next_stone = stones[currStoneIndex] + nextJump;

                if(mp.find(next_stone) != mp.end()) {
                    result = result || solve(stones, mp[next_stone], nextJump);
                }
            }
        }
        return result ;
    }
    bool canCross(vector<int>& stones) {
        n = stones.size();

        if(stones[1] != 1) {
            return false;
        }

        for(int i=0; i<n; i++) {
            mp[stones[i]] = i ;
        }

        return  solve(stones, 0, 0);
    }
};