class Solution {
public:
    void bfs(vector<int>& edges, int src, vector<int>& vis, vector<int>& dist_node1) {
        queue<int> que;
        que.push(src);
        dist_node1[src] = 0;
        vis[src] = 1;

        int cost = 0;

        while(que.size()) {
            int t = que.size();
            while(t--) {

                int curr = que.front();
                que.pop();
                dist_node1[curr] = cost ;
                int v = edges[curr];

                if(v != -1 && !vis[v]) {
                    vis[v] = 1 ;
                    que.push(v);
                }
            }

            cost++;
        }

    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        
        int n = edges.size();
        
        vector<int> dist_node1(n, INT_MAX);
        vector<int> dist_node2(n, INT_MAX);

        vector<int> vis1(n, 0);
        vector<int> vis2(n, 0);

        bfs(edges, node1, vis1, dist_node1);
        bfs(edges, node2, vis2, dist_node2);

        int minDistNode = -1;
        int maxDistTillNow = INT_MAX;

        for(int i=0; i<n; i++) {
            int maxD = max(dist_node1[i], dist_node2[i]);

            if(maxDistTillNow > maxD) {
                maxDistTillNow = maxD;
                minDistNode = i ;
            }
        }

        return minDistNode;
    }
};