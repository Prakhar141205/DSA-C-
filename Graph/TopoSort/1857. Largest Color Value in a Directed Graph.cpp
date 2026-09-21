class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        unordered_map<int, vector<int> > adj ;
        int n = colors.length();

        vector<int> indegree(n, 0);

        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            
            indegree[v]++;
        }

        queue<int> que;
        vector<vector<int>> t(n, vector<int> (26, 0)) ;

        for(int i=0; i<n; i++) {
            if(indegree[i] == 0) {
                que.push(i);
                t[i][colors[i] - 'a'] = 1 ;
            }
        }
        int ans = 0;
        int countNodes = 0;

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            countNodes += 1;
            ans = max(ans, t[u][colors[u] - 'a']) ;

            for(int v : adj[u]) {
                for(int c=0; c<26; c++) {
                    t[v][c] = max(t[v][c], t[u][c] + (colors[v] - 'a' == c)) ;
                }

                indegree[v]--;

                if(indegree[v] == 0) {
                    que.push(v);
                }
            }
        }

        return countNodes < n ? -1 : ans ; 
    }
};