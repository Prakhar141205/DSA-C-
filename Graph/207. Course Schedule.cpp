class Solution {
public:
    bool isCycleDFS(unordered_map<int, vector<int>>& adj, int src, vector<bool>& vis, vector<bool>& inRecursion) {
        vis[src] = true;
        inRecursion[src]=true;
        for(int& v : adj[src]) {
            if(!vis[v] && isCycleDFS(adj, v, vis, inRecursion)) return true;
            else if(inRecursion[v]) return true; 
        }

        inRecursion[src]=false;
        return false;
    }
    bool canFinish(int n, vector<vector<int>>& courses) {
        unordered_map<int, vector<int> > adj;

        for(auto& course : courses) {
            int dest = course[0];
            int src = course[1];
            adj[src].push_back(dest);
        }

        vector<bool> vis(n, false);
        vector<bool> inRecursion(n, false);

        for(int u=0; u<n; u++) {
           if(!vis[u] && isCycleDFS(adj, u, vis, inRecursion)) return false;
        }
        return true;
        
    }
};

// Kahns Algorithm

class Solution {
public:
    bool isCycleBFS(unordered_map<int, vector<int>>& adj, int n,vector<int>& inDegree) {
        queue<int> que;
        int cnt=0; // no of nodes that visited
        // push all the vertices with indegree equal 0 
        for(int i=0; i< n; i++) {
            if(inDegree[i] == 0) {
                cnt++;
                que.push(i);
            }
        }

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            for(auto& v : adj[u]) {
                inDegree[v]--;
                if(inDegree[v] == 0) {
                    cnt++;
                    que.push(v);
                }
            }
        }

        if(cnt == n) return true;
        return false;
    }
    bool canFinish(int n, vector<vector<int>>& courses) {
        unordered_map<int, vector<int> > adj;
        vector<int> inDegree(n);
        for(auto& course : courses) {
            int dest = course[0];
            int src = course[1];
            adj[src].push_back(dest);
            inDegree[dest]++;
        }
        

        
        return isCycleBFS(adj, n, inDegree);
        
    }
};