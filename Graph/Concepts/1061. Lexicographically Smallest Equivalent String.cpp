class Solution {
public:
    char dfs(unordered_map<char, vector<char>>& adj, char src, vector<int>& vis) {

        vis[src-'a'] = 1;
        char minChar = src;
        for(auto& v : adj[src]) {

            if(!vis[v-'a']) {
                minChar = min(minChar, dfs(adj, v, vis));
            }
        }

        return minChar ;
    }
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.length();
        unordered_map<char, vector<char>> adj(n);

        for(int i=0; i<n; i++ ) {
            char u = s1[i];
            char v = s2[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        string ans;
        for(char c : baseStr) {
            vector<int> vis(26, 0);
            ans.push_back(dfs(adj, c, vis));
        }
        return ans;
    }
};

// USing DSU and Path Compression
class Solution {
public:
class DisjointSet{
    public:
    vector<int>parent,size;
    DisjointSet(int n){
    parent.resize(n+1);
    size.resize(n+1);

    for(int i=0;i<=n;i++){
        parent[i]=i;
        size[i]=1;
    }
    }

    int findUPar(int node){
        if(parent[node]==node)return node;

        return parent[node]=findUPar(parent[node]);
    }

    void unite(char a, char b){
        int pa=findUPar(a-'a');
        int pb=findUPar(b-'a');

        if(pa==pb)return ;

        else if(pa>pb){
            parent[pa]=pb;
            size[pb]+=pa;
        }
        else {
            parent[pb]=pa;
            size[pa]+=pb;
        }
    }

};
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int m=size(s1),n=size(baseStr);
        DisjointSet ds(26);

        for(int i=0;i<m;i++){
            ds.unite(s1[i],s2[i]);
        }
        string ans;
        for(int i=0;i<n;i++){
            int p=ds.findUPar(baseStr[i]-'a');
            ans+=(char(p+'a'));
        }
        return ans;
    }
};

// Using simple dsu
class Solution {
public:
    vector<int> parent;

    int find(int u) {
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    } 

    void Union(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if(pu < pv ) {
            parent[pv] = pu;
        }else {
            parent[pu] = pv;
        }
    }
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = baseStr.length();

        parent.resize(26);
        for(int i=0; i<26; i++) {
            parent[i] = i;
        }
        
        for(int i=0; i<s1.length(); i++) {
            int par1 = find(s1[i] - 'a');
            int par2 = find(s2[i] - 'a');

            if(par1 != par2) Union(par1, par2);

        }

        string ans;
        for(char c : baseStr) {
            
            ans += (char)(find(c - 'a') + 'a' ) ;
        }
        return ans;
    }
};