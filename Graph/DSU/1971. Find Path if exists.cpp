class Solution {
public:
    vector<int> parent;
    vector<int> rank;
    int find(int x) {
        if(x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    } 

    void Union(int x, int y) {
        int par_x = find(x);
        int par_y = find(y);

        if(rank[par_x] > rank[par_y]) {
            parent[par_y] = par_x;
        }else if(rank[par_x] < rank[par_y]) {
            parent[par_x] = par_y;
        }else {
            parent[par_x] = par_y;
            rank[par_y] += 1;
        }
    }
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        // int n = edges.size();
        parent.resize(n);
        rank.resize(n, 1);

        for(int i=0; i<n; i++) {
            parent[i] = i ;
        }
        for(auto edge : edges ) {
            int u = edge[0];
            int v = edge[1];

            int par_u = find(u);
            int par_v = find(v);

            if(par_u != par_v) {
                Union(par_u, par_v);
            }
        }
        
        return find(source) == find(destination);
    }
};