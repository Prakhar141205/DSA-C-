class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        if (restrictions.size() == 0)return n - 1;

        sort(restrictions.begin(), restrictions.end(), [](auto&& x, auto&& y) {return x[0] < y[0]; });

        int curId = 1;
        int curHeight = 0;

        // First pass, only consider left buildings.
        for (auto&& x : restrictions) {
            x[1] = min(x[1], x[0] - curId + curHeight);
            curId = x[0];
            curHeight = x[1];
        }

        // Second pass, only consider rights buildings
        for (int i = restrictions.size() - 2; i >= 0; i--) {
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + restrictions[i + 1][0] - restrictions[i][0]);
        }
        
        // Get answer. The last building is the special case since no restriction on its right side.
        auto res = n - restrictions[restrictions.size() - 1][0] + restrictions[restrictions.size() - 1][1];
        curId = 1;
        curHeight = 0;
        for (auto&& x : restrictions) {
            // Given two restricted building's height, what's the maximum building height in their intervals? 
            // First, we should compensate two building's height difference. The remained buildings can be built higher.
            int steps = x[0] - curId - abs(x[1] - curHeight);
            int higher = max(x[1], curHeight);
            // Remember to step down if we step up. Hence divide by 2.
            res = max(res, higher + steps / 2);
            curId = x[0];
            curHeight = x[1];
        }

        return res;
    }
};