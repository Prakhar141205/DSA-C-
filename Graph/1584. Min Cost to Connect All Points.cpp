class Solution {
public:
    typedef pair<int, int> P ;
    int minCostConnectPoints(vector<vector<int>>& points) {
        unordered_map<int, vector<pair<int, int>>> adj ;
        int n = points.size() ;

        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                int dist = (abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])) ;
                adj[i].push_back({j, dist}) ;

                adj[j].push_back({i, dist}) ;
            }
        }

        priority_queue<P, vector<P>, greater<P> > pq ;

        pq.push({0, 0}) ;
        int sum = 0 ;
        vector<bool> inMst(n, false) ;

        while(!pq.empty()) {
            auto [wt, node] = pq.top();
            pq.pop();

            if(inMst[node]) continue;

            inMst[node] = true;
            sum += wt ;

            for(auto& [ngbr_node, ngbr_wt] : adj[node]) {

                if(!inMst[ngbr_node]) {
                    pq.push({ngbr_wt, ngbr_node}) ;
                }
            }
            
        }

        return sum ;
    }
};