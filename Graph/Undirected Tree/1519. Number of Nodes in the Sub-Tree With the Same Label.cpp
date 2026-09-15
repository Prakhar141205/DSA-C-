class Solution {
public:
    vector<int> parent;
    void buildParent(vector<vector<int>>& adj, int src, int par) {
        parent[src] = par;
        for(auto& v : adj[src]) {

            if(v == par) continue;

            buildParent(adj, v, src);
        }

    } 
    int dfs(vector<vector<int>>& adj, int src, string& labels,  char target) {

        int cnt = 0;
        if(labels[src] == target) cnt += 1 ;

        for(auto& v : adj[src]) {
            if(v == parent[src]) continue;

            cnt += dfs(adj, v, labels, target);
        }
        return cnt;
    }
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> adj(n);

        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            
        }
        parent.resize(n);
        buildParent(adj, 0, -1);
        vector<int> ans(n);

        for(int i=0; i<n; i++) {
            ans[i] = dfs(adj, i, labels, labels[i]);
        }

        return ans;
    }
};

// Clean O(n ) Solution
class Solution {
public:
    vector<int> ans;
   
    vector<int> dfs(vector<vector<int>>& adj, int src, int par, string& labels) {

        vector<int> freq(26);

        freq[labels[src] - 'a']++;

        for(auto& v : adj[src]) {
            if(v == par) continue;

            vector<int> child = dfs(adj, v, src, labels);

            for(int i=0; i<26; i++) {
                freq[i] += child[i];
            }
        }
        ans[src] = freq[labels[src] - 'a'];
        return freq;
    }
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> adj(n);

        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            
        }
        ans.resize(n);
        dfs(adj, 0, -1, labels);
        return ans;
    }
};

// Optimized without using multiple freq vector
class Solution {
public:
    void dfs(vector<vector<int>>& adj, int curr, int par, vector<int>& count, vector<int>& ans, string& labels) {

        char myLabel = labels[curr];
        int cnt_before_vis_curr_child = count[myLabel - 'a'];

        count[myLabel - 'a']++;
        for(int& v : adj[curr]) {
            if(v == par) continue;
            dfs(adj, v, curr, count, ans, labels);
        }

        int cnt_after_vis_curr_child = count[myLabel-'a'];
        ans[curr] = cnt_after_vis_curr_child - cnt_before_vis_curr_child ;
    }
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> adj(n);

        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            
        }

        
        vector<int> ans(n);
        vector<int> count(26, 0);

        dfs(adj, 0, -1, count, ans, labels);

        return ans;
    }
};