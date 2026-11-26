class Solution {
  public:
    vector<int> parent;
    vector<int> rank;

    int find(int x) {
        if (x == parent[x])
            return x;

        return parent[x] = find(parent[x]);
    }

    void Union(int x, int y) {
        int xp = find(x);
        int yp = find(y);

        if (xp == yp) return;

        if (rank[xp] > rank[yp]) {
            parent[yp] = xp;
        }
        else if (rank[xp] < rank[yp]) {
            parent[xp] = yp;
        }
        else {
            parent[xp] = yp;
            rank[yp]++;
        }
    }

    int krushkalAlgo(vector<vector<int>>& adj) {
        int s = 0;

        for (auto temp : adj) {
            int u = temp[0];
            int v = temp[1];
            int wt = temp[2];

            if (find(u) != find(v)) {
                Union(u, v);
                s += wt;
            }
        }

        return s;
    }

    int primMST(vector<vector<vector<int>>>& mp) {
        int V = mp.size();

        parent.resize(V);
        rank.assign(V, 0);

        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        vector<vector<int>> adj;

        // Convert adjacency list into edge list
        for (int u = 0; u < V; u++) {
            for (auto vec : mp[u]) {
                int v = vec[0];
                int wt = vec[1];

                if (u < v) {
                    adj.push_back({u, v, wt});
                }
            }
        }

        // Sort edges by weight
        sort(adj.begin(), adj.end(),
             [](auto a, auto b) {
                 return a[2] < b[2];
             });

        return krushkalAlgo(adj);
    }
};