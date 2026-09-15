class Graph {
public:
    vector<vector<pair<int, int>>> adj;
    int n ;
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj.resize(n);

        for(auto& e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back({v, e[2]});
        }
        
    }
    
    void addEdge(vector<int> edge) {
        adj[edge[0]].push_back({edge[1], edge[2]});
        
    }
    
    int shortestPath(int node1, int node2) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
        vector<int> ans(n, INT_MAX);

        ans[node1] = 0 ;
        pq.push({0, node1});

        while(pq.size()) {
            auto [d, node] = pq.top();
            pq.pop();

            for(auto v : adj[node]) {
                int adjNode = v.first;
                int cost = v.second;

                if(d + cost < ans[adjNode]) {
                    ans[adjNode] = d + cost ;
                    pq.push({d+cost, adjNode});
                }
            }
        }

        return ans[node2] != INT_MAX ? ans[node2] : -1;
        
    }
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */