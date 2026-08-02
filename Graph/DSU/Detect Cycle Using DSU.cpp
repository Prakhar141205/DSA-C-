class Solution {
  public:
    vector<int> parent;
    vector<int> rank ;
    int find(int i) {
        if(i == parent[i]) return i;
        
        return parent[i] = find(parent[i] ) ;
        
    }
    
    void Union(int x, int y) {
        int x_par = find(x) ;
        int y_par = find(y) ;
        
        
        if(x_par == y_par) {
            return ;
        }
        
        if(rank[x_par] > rank[y_par]) {
            parent[y_par] = x_par;
            
        }else if(rank[y_par] > rank[x_par]) {
            parent[x_par] = y_par ;
        }else {
            parent[x_par] = y_par;
            rank[y_par]++;
        }
    }
    bool detectCycle(int V, vector<int> adj[]) {
        parent.resize(V);
        rank.resize(V, 0) ;
        
        for(int i=0; i<V; i++) {
            parent[i] = i ;
            rank[i] = 1 ;
        }
        
        for(int i=0; i<V; i++) {
            for(int v : adj[i]) {
                if(i < v) {
                    if(find(i) == find(v)) return true;
                    Union(i, v ) ;
                }
            }
        }
        
        return false ;
    }
};