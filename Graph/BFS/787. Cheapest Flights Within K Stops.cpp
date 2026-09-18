class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        unordered_map<int, vector<pair<int, int>> > adj ;

        for(auto& flight : flights) {
            int u = flight[0];
            int v = flight[1];
            int wt = flight[2];

            adj[u].push_back({v, wt});
        }
          
         vector<int> res(n, INT_MAX);
         queue<pair<int, int>> que; // cost, node

         que.push({0, src}) ;
         res[src] = 0;
        int steps = 0;
         while(!que.empty()) {
            int t = que.size();
            
            while(t--) {
                auto [cost, node] = que.front();
                que.pop();

                for(auto [v, wt] : adj[node]) {

                    if(wt + cost < res[v]) {
                        res[v] = wt + cost ;
                        que.push({wt + cost, v});
                    }
                }
            }
            steps++;
            cout << steps << " ";
            if(steps == k+1) break;
         }

         return res[dst] == INT_MAX ? -1 : res[dst] ;

    }
};