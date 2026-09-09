class Solution {
public:
    vector<vector<int>> ans ;
    int n;
    void dfs( vector<vector<int>>& graph, int src, vector<int>& temp) {
        
        temp.push_back(src);
        if(src == n-1) {
            ans.push_back(temp);
            temp.pop_back();

            return;
        }
        for(int v : graph[src]) {
            
            dfs(graph, v, temp);
        }

        temp.pop_back();
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        n = graph.size();
        vector<int> temp;
        
        dfs(graph, 0, temp);
        return ans;
        
    }
};