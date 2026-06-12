const int M = 1e9+7;
class Solution {
public:
    typedef long long ll;
    ll power(ll base, ll expo){
        if(expo == 0) return 1;

        ll half = power(base, expo/2);

        ll ans = (half*half)%M;

        if(expo % 2 != 0){
            ans = (ans*base)%M;
        }

        return ans;
    }
    int getMaxDepth( unordered_map<int, vector<int>>& m, int node, int parent){
        int maxDepth = 0;

        for(int &ngbr : m[node]){
            if(ngbr == parent) continue;
            maxDepth = max(maxDepth, getMaxDepth(m, ngbr, node)+1);
        }
        return maxDepth;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {
       
        int n = edges.size();
        unordered_map<int, vector<int>> m;
        for(auto& edge : edges){
            int u = edge[0];
            int v = edge[1];

            m[u].push_back(v);
            m[v].push_back(u);
        }
        auto maxDepth = getMaxDepth(m, 1, -1);
        int ans = (int)power(2, maxDepth-1);
        return ans%M;
    }
};