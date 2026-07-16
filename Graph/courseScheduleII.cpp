class Solution {
public:
    bool isCycleDFS(int src, vector<vector<int>>& adj, vector<int>& visited, vector<int>& inRecursion) {
        visited[src] = 1;
        inRecursion[src] = 1;

        for(auto& v : adj[src]){
            if(!visited[v] && isCycleDFS(v, adj, visited, inRecursion)) return true;
            else if(inRecursion[v]) return true;
        }
        inRecursion[src] = 0;
        return false;
    }
    // toposort
    void dfs(vector<vector<int>>& adj, int src, vector<int>& vis, stack<int>& st) {
        vis[src] = 1;
        for(auto& v : adj[src]) {
            if(!vis[v]) 
                dfs(adj, v, vis, st) ;
        }
        st.push(src);
    }
    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        // if(prerequisites.size() == 0) {
        //     vector<int> v;
        //     for(int i=0; i<n; i++) {
        //         v.push_back(i);
        //     }
        //     return v;
        // }
        vector<vector<int>> adj(n);    

        for(auto& v : prerequisites) {
            int dest = v[0];
            int src = v[1];

            adj[src].push_back(dest);
        }  

        vector<int> vis(n, 0);
        vector<int> inRecursion(n, 0);

        stack<int> st;
        vector<int> ans;
        for(int u=0; u<n; u++) {
            if(!vis[u] && isCycleDFS(u, adj, vis, inRecursion)) return {};
            
        }
        vis.assign(n, 0) ;
        for(int u=0; u<n; u++) {
            if(!vis[u]) {
                dfs(adj, u, vis, st);
            }
        }
        
        while(st.size()) {
            ans.push_back(st.top());
            st.pop();
        }
        return ans;
    }
};