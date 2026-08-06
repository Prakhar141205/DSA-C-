class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
       vector<int> result(V, 1e8);
       
       result[src] = 0 ;
       
       for(int cnt=1; cnt <= V-1; cnt++) {
           
           for(auto edge : edges) {
               int u = edge[0];
               int v = edge[1];
               int wt = edge[2] ;
               
                if(result[u] != 1e8 && result[u] + wt < result[v]) {
                    result[v] = result[u] + wt ;
                }
           }    
       }
       
       // check if one more time edges gets  relaxed implies negative cycle in graph exists
      for(auto edge : edges) {
               int u = edge[0];
               int v = edge[1];
               int wt = edge[2] ;
               
                if(result[u] != 1e8 && result[u] + wt < result[v]) {
                    return {-1 } ;
                }
           } 
        
        return result;
    }
};
