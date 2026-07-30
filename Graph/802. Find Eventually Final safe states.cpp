class Solution {
public:
    vector<int> safeNodes;
    bool dfs(vector<vector<int>>& graph, int src, vector<int>& vis, vector<bool>& inRecursion) {

        vis[src] = 1;
        inRecursion[src] = true ;
        

        for(auto& ngbr : graph[src]) {
            if(!vis[ngbr] && dfs(graph, ngbr, vis, inRecursion)) {
                return true; 
            }else if(inRecursion[ngbr]) return true;
        }

        inRecursion[src] = false;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
       
        int V = graph.size(); 

        vector<int> vis(V, 0) ;
        vector<bool> inRecursion(V, false) ;

        for(int i=0; i<V; i++) {
            if(!vis[i])
                dfs(graph, i, vis, inRecursion);
        }

        for(int i=0; i<V; i++) {
            if802802(inRecursion[i] == false) {
                safeNodes.push_back(i);
            }
        }  
        return safeNodes;
    }
};