class Solution {
public:
    int BFS(int st, unordered_map<int, vector<int>>& adj, vector<bool>& vis) {

        queue<pair<int, int>> que ;

        que.push({st, 0});
        int maxDist = 0;

        while(!que.empty()) {
            auto [currNode, dist] = que.front();
            que.pop();

            for(auto& ngbr : adj[currNode]) {
                if(!vis[ngbr]) {
                    vis[ngbr] = true;
                    que.push({ngbr, dist+1});
                    maxDist = max(maxDist, dist+1);
                }
            }
        }
        return maxDist;
    }
     int maximumInvitations(vector<int>& fav) {
        int n = fav.size();
        unordered_map<int, vector<int>> adj;

        for(int i=0; i<n; i++) {
            int u = i;

            int v = fav[i];

            adj[v].push_back(u);
        }

        int longestCycleEmpCount = 0;
        int happyCoupleCount = 0;
        vector<bool> visited(n, false);

        for(int i=0; i<n; i++) {

            if(!visited[i]) {
                unordered_map<int, int > mp;
                int currNode = i;

                int currNodeCount = 0;

                while(!visited[currNode]) {
                    visited[currNode] = true;
                    mp[currNode] = currNodeCount;

                    int nextNode = fav[currNode];
                    currNodeCount += 1;

                    if(mp.count(nextNode)) {

                        int cycleLength = currNodeCount - mp[nextNode];

                        longestCycleEmpCount = max(longestCycleEmpCount, cycleLength); 

                        if(cycleLength == 2)  {
                            vector<bool> visNodes(n, false);
                            visNodes[currNode] = true;
                            visNodes[nextNode] = true; 
                            happyCoupleCount += 2 + BFS(currNode, adj, visNodes) + BFS(nextNode, adj, visNodes); 
                        }

                        break;
                    }

                    currNode = nextNode ;
                }
            }
        }

        return max(happyCoupleCount, longestCycleEmpCount);
    }
};