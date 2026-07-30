class Solution {
public:
    vector<int> parent;
    vector<int> rank;


    int find(int x) {
        if(x == parent[x]) return x ;
        
        return parent[x] = find(parent[x]);

    }


    void Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y) ;

        if(x_parent == y_parent) return;

        if(rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        }else if(rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        }else {
            parent[x_parent] = y_parent;
            rank[y_parent]++; 
        }
    }
    long long countPairs(int n, vector<vector<int>>& edges) {
        parent.resize(n);
        rank.resize(n, 0);

        for(int i=0; i<n; i++) {
            parent[i] = i;
        }

        for(auto& edge : edges ) {
            int u = edge[0];
            int v = edge[1];

            Union(u, v) ;
        }

        unordered_map<int, int> mp; // representative, component size

        for(int i=0; i<n; i++) {
            int representative = find(i);

            mp[representative]++;
        }

        long long size = n ;
        long long res = 0 ;
        for(auto [repre, sz] : mp) {
            res += (sz) * (size - sz) ;

            size = (size - sz) ;
        }

        return res ;
    }
};