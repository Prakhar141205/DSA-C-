class Solution {
    bool isCycleDFS(int src, vector<int>& adj[], vector<int>& visited, vector<int>& inRecursion) {
        visited[src] = 1;
        inRecursion[src] = 1;

        for(auto& v : adj[src]){
            if(!visited[v] && isCycleDFS(v, adj, visited, inRecursion)) return true;
            else if(inRecursion[v]) return true;
        }
        inRecursion[src] = 0;
        return false;
    }
    bool isCycleDFSInDAG(int V, vector<int>& adj[]) {
        vector<int> visited(V, 0);
        vector<int> inRecursion(V, 0);

        for(int i=0; i<V; i++) {
            if(!visited[i]  && isCycleDFS(adj, src, visited, inRecursion)) {
                return true;
            }
        }
        return false;
    }


};