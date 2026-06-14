const int MX = 100001;
const int MOD = 1e9 + 7;

long long fac[MX], inv_fac[MX];

void precompute() {
    if (fac[0] == 1) return;
    fac[0] = 1;
    for (int i = 1; i < MX; i++) fac[i] = fac[i-1] * i % MOD;
    inv_fac[MX-1] = 1;
    long long base = fac[MX-1], exp = MOD - 2, result = 1, mod = MOD;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    inv_fac[MX-1] = result;
    for (int i = MX - 2; i >= 0; i--) inv_fac[i] = inv_fac[i+1] * (i+1) % MOD;
}

class Solution {
    int n;
    vector<vector<int>> g;
    vector<vector<pair<int,int>>> q;
    vector<int> lca_ans, deep, uf;
    vector<bool> vis;

    int find(int x) {
        while (uf[x] != x) {
            uf[x] = uf[uf[x]];
            x = uf[x];
        }
        return x;
    }

    void tarjan(int u, int parent) {
        vis[u] = true;
        for (int v : g[u]) {
            if (v == parent) continue;
            tarjan(v, u);
            uf[v] = u;
        }
        for (auto [node, idx] : q[u]) {
            if (vis[node]) lca_ans[idx] = find(node);
        }
    }

    void dfs(int u, int fa, int d) {
        deep[u] = d;
        for (int v : g[u]) {
            if (v == fa) continue;
            dfs(v, u, d + 1);
        }
    }

    long long power(long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    }

public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        precompute();

        n = edges.size() + 1;
        g.assign(n + 1, {});
        q.assign(n + 1, {});
        lca_ans.assign(queries.size(), 0);
        deep.assign(n + 1, 0);
        uf.resize(n + 1);
        iota(uf.begin(), uf.end(), 0);
        vis.assign(n + 1, false);

        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        for (int i = 0; i < (int)queries.size(); i++) {
            q[queries[i][0]].emplace_back(queries[i][1], i);
            q[queries[i][1]].emplace_back(queries[i][0], i);
        }

        tarjan(1, 0);
        dfs(1, 0, 0);

        vector<int> ans(queries.size());
        for (int i = 0; i < (int)queries.size(); i++) {
            int x = deep[queries[i][0]] + deep[queries[i][1]] - 2 * deep[lca_ans[i]];
            ans[i] = (x == 0) ? 0 : (int)power(2, x - 1, MOD);
        }
        return ans;
    }
};

static constexpr size_t max_align = alignof(max_align_t);
alignas(max_align) static unsigned char BUFFER[200 * 1024 * 1024];
static size_t pos = 0;

void *operator new(const size_t size) {
    const size_t padding = (max_align - (pos % max_align)) % max_align;
    pos += padding + size;
    return static_cast<void *>(&BUFFER[pos - size]);
}

void *operator new[](const size_t size) { return operator new(size); }
void operator delete(void *) noexcept {}
void operator delete[](void *) noexcept {}
void operator delete(void *, size_t) noexcept {}
void operator delete[](void *, size_t) noexcept {}

// method 2

typedef long long ll;
const int M = 1e9+7;
class Solution {
public:
    void bfs(int root, vector<vector<int>>& adj, vector<int>& depth, vector<vector<int>>& up){
        queue<pair<int, int>> q;

        q.push({root, 1}); // {node, parent}

        depth[root]=0;
        up[root][0] = 1;

        while(!q.empty()){
            auto [node, parent] = q.front();
            q.pop();

            for(int child: adj[node]){
                if(child != parent){
                    depth[child] = depth[node]+1;
                    up[child][0]= node;
                    q.push({child, node}); 
                }
            }
        }
    }

    int getLCA(int u, int v, vector<int>& depth, vector<vector<int>>& up){

        // ensure u is the deeper node
        if(depth[u] < depth[v]) swap(u, v);

        // bring u to the same depth
        int diff = depth[u]-depth[v];

        for(int j=19; j>=0; j--){
            if((diff >> j) & 1){
                u = up[u][j];
            }
        } 

        if(u == v) return u;

        // jump both u and v simultaneously

        for(int j=19; j>=0; j--){
            if(up[u][j] != up[v][j]){
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }
    ll power(ll base, ll expo){
        if(expo < 0) return 0;
        ll res = 1;
        while(expo > 0){
            if(expo & 1) res = (res*base)%M;

            base = (base*base)%M;
            expo >>= 1;
        }
        return res;
    }
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size()+1;
        vector<vector<int>> adj(n+1);

        for(auto& e: edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> depth(n+1, 0);
        vector<vector<int>> up(n+1, vector<int> (20, 0));

        // initialize depth and 2^0 ancestor
        bfs(1, adj, depth, up);

        // precompute binary lifting table
        for(int j=1; j<20; j++){

            for(int i=1; i<=n; i++){
                up[i][j] = up[up[i][j-1]][j-1];
            }
        }
        

        vector<int> ans;
        ans.reserve(queries.size());

        for(auto& q: queries){
            int u=q[0];
            int v = q[1];

            if(u == v){
                ans.push_back(0);
                continue;

            }

            int lca = getLCA(u, v, depth, up);
            int L = depth[u] + depth[v] - 2*depth[lca];

            ans.push_back(power(2, L-1));
        }

        return ans;
    }
};