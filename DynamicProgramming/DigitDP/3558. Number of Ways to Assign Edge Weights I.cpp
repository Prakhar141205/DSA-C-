class Solution {
public:
    long long MOD = 1e9+7; 
    vector<long long> pow2;
    int assignEdgeWeights(vector<vector<int>>& edges) {
        int n = edges.size()+1;
        vector<vector<int>> g(n);
        for(auto &e:edges){
            int u = e[0]-1, v = e[1]-1;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int> depth(n, -1);
        queue<int> q;
        depth[0] = 0;
        q.push(0);

        pow2.resize(n);
        pow2[0] = 1;

        for(int i=1; i<n; i++){
            pow2[i] = (pow2[i-1] << 1) % MOD;
        }

        int maxDepth = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            maxDepth = max(maxDepth, depth[u]);
            for(int v: g[u]){
                if(depth[v] == -1){
                    depth[v] = depth[u]+1;
                    q.push(v);
                }
            }
        }
        return pow2[maxDepth-1];
    }
};

class Solution {
public:
    int maxi = 0;
    const int MOD = 1000000007;

    void dfs(int i, vector<vector<int>>& v, vector<bool>& vis, int depth) {
        vis[i] = true;

        maxi = max(maxi, depth);

        for (auto it : v[i]) {
            if (!vis[it]) {
                dfs(it, v, vis, depth + 1);
            }
        }
    }
    int ans(int count, bool is_odd) {
        if (count == 0 && is_odd) return 1;
        if (count == 0) return 0;

        return (ans(count - 1, true) +
                ans(count - 1, false)) % MOD;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {

        int n = edges.size() + 1;

        vector<vector<int>> v(n + 1);

        vector<bool> vis(n + 1, false);

        for (auto it : edges) {
            v[it[0]].push_back(it[1]);
            v[it[1]].push_back(it[0]);
        }

        dfs(1, v, vis, 1);
        long long ans = 1;

        for(int i=1;i<maxi-1;i++){
            ans = (ans * 2) % MOD;
        }

        return ans;
    }
};