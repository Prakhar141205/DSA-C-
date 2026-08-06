class Solution {
public:
    void dfs(unordered_map<int, vector<int>> & adj, int src, vector<bool>& vis) {
        if(vis[src]) return ;
        vis[src] = true;
        for(auto& ngbr : adj[src] ) {
            if(!vis[ngbr]) {
                dfs(adj, ngbr, vis);
             }
        }
    }
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        unordered_map<int, vector<int> > adj;

        for(auto& inv : invocations) {
            int u = inv[0];
            int v = inv[1];

            adj[u].push_back(v) ;
        }

        // contains all the nodes that can be reached from kth node
        // true => suspciious
        vector<bool> vis(n, false);

        dfs(adj, k, vis) ;

        // now check 
        bool isAllUnsuspicious = false ;
        for(int u=0; u<n; u++) {
            for(auto v : adj[u]) {
                
                if(!vis[u]) {
                    if(vis[v]) { // not suspiciiosu to suspicios implies v also not suspicios
                        isAllUnsuspicious = true;
                    }
                }
            }
        }
        vector<int> ans ;
        for(int i=0; i<n; i++) {
            if(!vis[i]) {
                ans.push_back(i);
            }
        }
        vector<int> allNodes;
        for(int i=0; i<n; i++) {
            allNodes.push_back(i) ;
        }
        return isAllUnsuspicious ? allNodes: ans ;
    }
};

// BFS 
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        unordered_map<int, vector<int> > adj;
        vector<int> indegree(n, 0);
        vector<bool> suspicious(n, false);

         for(auto& inv : invocations) {
            int u = inv[0];
            int v = inv[1];

            adj[u].push_back(v) ;
            indegree[v]++;
        }

        queue<int> que;
        que.push(k) ;
        suspicious[k] = true ;

        while(!que.empty()) {
            int curr = que.front();
            que.pop() ;

            for(int ngbr : adj[curr]) {
                indegree[ngbr]--;

                if(!suspicious[ngbr]) {
                    que.push(ngbr);
                    suspicious[ngbr] = true ;
                }
            }
        }


        vector<int> ans ;
        bool cannotRemove  = false ;

        for(int i=0; i<n; i++) {
            if(suspicious[i] && indegree[i] > 0) {
                cannotRemove = true ;
                break;
            }

            if(!suspicious[i]) {
                ans.push_back(i);
            }
        }
        vector<int> res ;
        if(cannotRemove) {
            
            for(int i=0; i<n; i++) {
                res.push_back(i);
            }
        }
        return cannotRemove ? res: ans ;
    }
};L