class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        
        vector<int> dist(V, 1e8);
        dist[src] = 0;
         
        for(int i=1; i<=V-1; i++) {
            
            for(auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];
                if(dist[u] != 1e8 and dist[u] + wt < dist[v]) {
                    dist[v] = wt + dist[u];
                }
            }
        }
        
        // detect the cycle 
        for(auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];
                if(dist[u] != 1e8 and dist[u] + wt < dist[v]) {
                    return {-1} ;
                }
        }
        
        return dist;
        
    }
};
