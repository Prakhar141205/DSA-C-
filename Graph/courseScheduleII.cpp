class Solution {
public:
    bool dfs(unordered_map<int, vector<int>>& adj, int src, vector<bool>& vis, vector<bool>& inrecursion, stack<int>& sta) {
        vis[src] = true;
        inrecursion[src] = true;

        for(int v : adj[src]) {
            if(!vis[v]) {
                if(dfs(adj, v, vis, inrecursion, sta)) return true;
            }else if(inrecursion[v]) return true;
        }

        sta.push(src);
        inrecursion[src] = false;

        return false;
    }
    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> adj;
        for(auto p : prerequisites) {
            adj[p[1]].push_back(p[0]);
        }

        stack<int> sta;
        vector<bool> vis(n,false);
        vector<bool> inrecursion(n,false);

        for(int i=0; i<n; i++) {
            if(!vis[i]) {
                if(dfs(adj, i, vis, inrecursion, sta) ) {
                    return vector<int> {};
                }
            }
        }

        vector<int> ans;
        while(!sta.empty()) {
            ans.push_back(sta.top()) ;
            sta.pop();
        }
        
        return ans;
    }
};