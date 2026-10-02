
class DSU {
public:
    vector<int> parent;
    vector<int> rank;
    int components;

    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1);
        for(int i=0; i<=n; i++) {
            parent[i] = i;
            rank[i] = 1 ;
        }
        components = n ;
    }

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
            rank[par_x]++;
            parent[par_y] = par_x;
        }

        components--;
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        int totalGivenEdge = edges.size();

        sort(begin(edges), end(edges), [&](auto& v1, auto& v2) {
            return v1[0] > v2[0] ;
        });
        DSU Alice(n);
        DSU Bob(n);
        int edgeCount = 0;
        for(auto& edge : edges) {

            int type = edge[0];
            int u = edge[1];
            int v = edge[2];

            if(type == 3) {
                bool isAddEdge = false;

                if(Alice.find(u) != Alice.find(v)) {
                    Alice.Union(u, v);
                    isAddEdge = true;
                }

                if(Bob.find(u) != Bob.find(v)) {
                    Bob.Union(u, v);
                    isAddEdge = true;
                }
                
                edgeCount += (isAddEdge);
        
        }else if(type == 2) {
            if(Bob.find(u) != Bob.find(v)) {
                    Bob.Union(u, v);
                    edgeCount += 1;
                }
        }else {
            if(Alice.find(u) != Alice.find(v)) {
                    Alice.Union(u, v);
                    edgeCount += 1;
            }
        }
        }
        return (Alice.components == 1 && Bob.components == 1) ? (totalGivenEdge - edgeCount) : -1 ;
        
    }
};