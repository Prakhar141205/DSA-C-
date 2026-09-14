class Solution {
public:
    int dfs(vector<vector<int>>& adj, int src, int par, vector<bool>& hasApple) {
        int time = 0;

        for(auto& child : adj[src]) {
            if(child == par ) continue;

            int time_from_child = dfs(adj, child, src, hasApple);

            if(time_from_child > 0 || hasApple[child]) {
                time += (2 + time_from_child);
            }
        }

        return time;
    }
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>> adj(n);

        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        return dfs(adj, 0, -1, hasApple);

    }
};