
class Solution {
public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges,
                             int src, int dest) {

        vector<vector<pair<int,int>>> adj(V + 1);

        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        using P = pair<long long, int>;

        const long long INF = LLONG_MAX;

        vector<long long> dist(V + 1, INF);

        priority_queue<P, vector<P>, greater<P>> pq;

        dist[dest] = 0;
        pq.push({0, dest});

        // Dijkstra from destination
        while(!pq.empty()) {

            auto [d, u] = pq.top();
            pq.pop();

            if(d != dist[u]) continue;

            for(auto& [v, wt] : adj[u]) {

                if(d + wt < dist[v]) {
                    dist[v] = d + wt;
                    pq.push({dist[v], v});
                }
            }
        }

        if(dist[src] == INF) return {-1};

        // Reconstruct lexicographically smallest path
        vector<int> ans;
        int u = src;

        ans.push_back(u);

        while(u != dest) {

            int nextNode = -1;

            sort(adj[u].begin(), adj[u].end());

            for(auto& [v, wt] : adj[u]) {

                if(dist[u] == dist[v] + wt) {
                    nextNode = v;
                    break;
                }
            }

            if(nextNode == -1) return {-1};

            u = nextNode;
            ans.push_back(u);
        }

        return ans;
    }
};
