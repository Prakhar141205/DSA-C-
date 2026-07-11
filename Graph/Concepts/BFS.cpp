class Solution {
  public:
    vector<int> ans;
    
    void solve(vector<vector<int>>& adj, int u, vector<bool>& vis) {
        queue<int> que;
        
        que.push(u);
        vis[u]=true;
        ans.push_back(u);
        
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            
            for(auto& v : adj[u]) {
                if(!vis[v]) {
                    que.push(v);
                    vis[v]=true;
                    ans.push_back(v);
                }
            }
        }
    }
    vector<int> bfs(vector<vector<int>> &adj) {
        vector<bool> vis(adj.size(), false);
        solve(adj, 0, vis);
        
        return ans;
        // code here
        
    }
};