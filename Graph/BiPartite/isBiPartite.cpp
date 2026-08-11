class Solution {
public:
    bool dfs(vector<vector<int>>&  adj, int src, vector<int>& color, int currColor) {

        color[src] = currColor ;

        for(int& ngbr : adj[src]) {

            if(color[ngbr] == color[src]) return false;

            if(color[ngbr] == -1) {
                int colorOfV = 1 - currColor;

                if(!dfs(adj, ngbr, color, colorOfV)) return false;
            }
        }

        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();

        vector<int> color(n, -1) ;

        for(int i=0; i<n; i++) {

            if(color[i] == -1) {

                if(!dfs(graph, i, color, 1)) {
                    return false;
                }
            }
        }
        
        return true;
    }
};