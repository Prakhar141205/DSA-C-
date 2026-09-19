class Solution {
public:
    int result = -1;

    void dfs(vector<int>& edges, int src, vector<bool>& in_recursion, vector<bool>& vis, vector<int>& count) { 
        if(src != -1 ) {
            vis[src] = true;
            in_recursion[src] = true;

            // get the neighbours
            int v = edges[src];

            // if not visited than mark visited by calling furhter
            if(v != -1) {
                if(!vis[v]) {
                    count[v] = count[src] + 1 ;
                    dfs(edges, v, in_recursion, vis, count) ; 
                }else if(in_recursion[v]) {
                    int cnt = count[src] - count[v] + 1 ;
                    result = max(result, cnt);
                }
            }
            in_recursion[src] = false;
        }
    }
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<bool> vis(n, false);

        vector<bool> in_recursion(n, false);
        vector<int> count(n, 1) ;

        for(int i=0; i<n; i++) {
            if(!vis[i]) {
                dfs(edges, i, in_recursion, vis, count) ;
            }
        }
        return result ;
        
    }
};