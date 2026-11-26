class Solution {
  public:

    // First DFS: Store vertices in stack according to finishing time
    void dfsFill(int u, vector<vector<int>>& adj,
                 vector<int>& vis, stack<int>& st) {

        vis[u] = 1;

        // Visit all unvisited neighbours
        for(int& v : adj[u]) {
            if(!vis[v]) {
                dfsFill(v, adj, vis, st);
            }
        }

        // Push the vertex after visiting all its neighbours
        // This gives us the finishing-time order
        st.push(u);
    }

    // Second DFS: Traverse the reversed graph to find an SCC
    void dfs(vector<vector<int>>& adjReversed, int u,
             vector<int>& vis) {

        vis[u] = 1;

        // Visit all unvisited neighbours in the reversed graph
        for(int& v : adjReversed[u]) {
            if(!vis[v]) {
                dfs(adjReversed, v, vis);
            }
        }
    }

    int countSCC(vector<vector<int>>& adj) {

        int V = adj.size();

        // STEP 1: Perform DFS on the original graph
        // Store vertices in stack based on their finishing times
        stack<int> st;
        vector<int> vis(V, 0);

        for(int i = 0; i < V; i++) {
            if(!vis[i]) {
                dfsFill(i, adj, vis, st);
            }
        }

        // STEP 2: Create the transpose (reversed) graph
        // Reverse the direction of every edge u -> v into v -> u
        vector<vector<int>> adjReversed(V);

        for(int i = 0; i < V; i++) {
            for(int& v : adj[i]) {
                adjReversed[v].push_back(i);
            }
        }

        // STEP 3: Reset visited array for the second DFS
        vis.assign(V, false);

        int cnt = 0;

        // STEP 4: Process vertices in decreasing finishing-time order
        while(!st.empty()) {

            int node = st.top();
            st.pop();

            // If the vertex is unvisited, it belongs to a new SCC
            if(!vis[node]) {

                // Explore the complete SCC in the reversed graph
                dfs(adjReversed, node, vis);

                // Increment SCC count after completing this DFS
                cnt++;
            }
        }

        // Return the total number of Strongly Connected Components
        return cnt;
    }
};