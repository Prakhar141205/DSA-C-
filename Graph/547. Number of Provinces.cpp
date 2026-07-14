class Solution {
public:
    void dfs(unordered_map<int, vector<int>>& graph, vector<bool>& vis, int u){

        vis[u] = true;

        for(auto& ngbr : graph[u]){
            if(!vis[ngbr]){
                dfs(graph, vis, ngbr) ;
            }
        }   
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size() ;
        unordered_map<int, vector<int> > graph;

        for(int u=0; u < n; u++) {
            for(int v =0; v < n; v++) {
                if(isConnected[u][v] == 1) {
                    graph[u].push_back(v);
                    graph[v].push_back(u);
                }
            }
        }

        
        int cities = 0;
        vector<bool> vis(n, false);

        for(int i=0; i<n; i++) {
            if(!vis[i]) {
                dfs(graph, vis, i);
                cities++;
            }
        }
        return cities;
    }
};

// without making Graph just oding using given matric

class Solution {
public:
    void dfs(int node, vector<vector<int>>& isConnected, vector<int>& visited){
        visited[node] = 1;
        for(int j=0;j<isConnected.size();j++){
            if(isConnected[node][j] == 1 && visited[j] == 0)
                dfs(j, isConnected, visited);
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int provinces = 0, n = isConnected.size();
        vector<int> visited(n, 0);
        for(int i=0;i<n;i++){
            if(!visited[i]){
                provinces++;
                dfs(i, isConnected, visited);
            }
        }
        return provinces;
    }
};