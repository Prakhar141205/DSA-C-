#define all(x) std::begin(x), std::end(x) 
class Solution {
public:
    vector<int> parent;
    vector<int> rank;

    int find(int x) {
        if(x == parent[x] ) return x;
        return parent[x] = find(parent[x]);
    } 

    void Union(int x, int y) {
        int par_x = find(x);
        int par_y = find(y);

        if(par_x == par_y) return;

        if(rank[par_x] > rank[par_y]) {
            parent[par_y] = par_x;
        }else if(rank[par_y] > rank[par_x]) {
            parent[par_x] = par_y;
        }else {
            parent[par_x] = par_y;
            rank[par_y] +=  1;
        }
    }
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();

        parent.resize(n);
        rank.resize(n, 1);

        for(int i=0; i<n; i++) {
            parent[i] = i;
        }

        unordered_map<int, vector<int>> adj;

        for(auto& vec : edges) {
            int u = vec[0];
            int v = vec[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        map<int, vector<int>> val_to_nodes;

        for(int i =0; i<n; i++) {
            int val = vals[i];
            val_to_nodes[val].push_back(i);
        }

        int res = n ;
        vector<bool> is_active(n, false);

        for(auto& it : val_to_nodes) {
            vector<int> nodes = it.second;
            for(int& u : nodes) {

                for(int& v : adj[u]) {
                    if(is_active[v]) {
                        Union(u, v);
                    }
                }

                is_active[u] = true;
            }

            vector<int> tumhare_parents;

            for(int u : nodes) {
                int par_kaun_hai = find(u);
                tumhare_parents.push_back(par_kaun_hai);
            }

            sort(all(tumhare_parents));
            int sz = tumhare_parents.size();

            for(int i=0; i<sz; i++) {
                long long cnt = 0;
                int curr_parent = tumhare_parents[i];
                while(i < sz && tumhare_parents[i] == curr_parent) {
                    cnt++;
                    i++;
                } 
                i--;
                int ans_from_formula = ((cnt) * (cnt - 1)) / 2 ;
                res += ans_from_formula ;
            }
        }

        return res;
    }
};