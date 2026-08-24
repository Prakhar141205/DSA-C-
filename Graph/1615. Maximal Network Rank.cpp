class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        unordered_map<int, unordered_set<int>> adj;

        for(auto road : roads) {
            adj[road[0]].insert(road[1]);
            adj[road[1]].insert(road[0]);
        }
        
        int ans = -1;
        for(int i=0; i<n; i++) {

            for(int j=i+1; j<n; j++) {

                int i_rank = adj[i].size();
                int j_rank = adj[j].size();

                if(adj[i].find(j) != adj[i].end() ) {
                    ans = max(ans, i_rank + j_rank - 1);
                }else {
                    ans = max(ans, i_rank + j_rank);
                }
            }
        }

        return ans;
    }
};