class Solution {
public:
    int findVal(pair<int, int> P1, pair<int, int> P2, pair<int, int> P3) {
        int x1 = P1.first, x2 = P2.first, x3 = P3.first;
        int y1 = P1.second, y2 = P2.second, y3 = P3.second;

        return (x2-x1)*(y3-y2) - (x3-x2)*(y2-y1);
    }
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        sort(trees.begin(), trees.end()) ;

        deque<pair<int, int> > upper, lower ;

        vector<vector<int>> res;

        for(auto& point : trees) {
            int l = lower.size();

            int u = upper.size() ;


            while(l >= 2 && findVal(lower[(l-2)], lower[(l-1)], {point[0], point[1]}) < 0) {
                l--;
                lower.pop_back();
            } 
            // upper 
            while(u >= 2 && findVal(upper[(u-2)], upper[(u-1)], {point[0], point[1]}) > 0) {
                u--;
                upper.pop_back();
            } 

            lower.push_back({point[0], point[1]});
            upper.push_back({point[0], point[1]});
        }

        set<pair<int, int>> st(lower.begin(), lower.end());

        for(auto& it : upper) {
            st.insert({it.first, it.second});
        }

        for(auto& it : st) {
            res.push_back({it.first, it.second}) ;
        }
        return res;
    }
};