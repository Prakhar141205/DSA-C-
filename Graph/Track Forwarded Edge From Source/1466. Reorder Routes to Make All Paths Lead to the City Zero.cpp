/*
Logic:

Assign weight to each edge 
1 ==> edge is away from the source
0  ==> edge is towards the source

*/
class Solution {
public:
    int dfs(unordered_map<int, vector<pair<int, int>>>& adj, int src, vector<int>& vis) {
        if(vis[src]) return 0;

        vis[src] = 1;
        int cnt = 0;

        for(auto& [v, dir] : adj[src]) {
            if(vis[v]) continue;

            cnt += dir ; // 1 means there is actual forward edge that needs to be reversed
                        // 0 means there is no edge we have consider it for this question

            cnt += dfs(adj, v, vis);
        }
        return cnt;
    }
    int minReorder(int n, vector<vector<int>>& cns) {
        unordered_map<int, vector<pair<int, int>>> adj;

        for(auto& c : cns) {
            adj[c[0]].push_back({c[1], 1});
            adj[c[1]].push_back({c[0], 0});
        }
        vector<int> vis(n, 0);
        int ans = 0;
        for(int i=0; i<n; i++) {

            if(!vis[i]) {
                ans += dfs(adj, i, vis);
            }
        }

        return ans;

        
    }
};