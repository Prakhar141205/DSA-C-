class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> mp ;
        for(auto& vec : times) {
            int u = vec[0];
            int v = vec[1];
            int wt = vec[2] ;

            mp[u].push_back({v, wt});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
        vector<int> result(n+1, INT_MAX);

        result[k] = 0;

        pq.push({0, k}) ;

        while(!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            for(auto& v : mp[node]) {
                int adjNode = v.first;
                int wt = v.second ;

                if(d + wt  < result[adjNode]) {
                    result[adjNode] = d + wt ;

                    pq.push({d + wt, adjNode}) ;
                }

            }


        }
        
        int M = *max_element(result.begin() +1 , result.end()) ;

        return M == INT_MAX ? -1 : M ;
    }
};