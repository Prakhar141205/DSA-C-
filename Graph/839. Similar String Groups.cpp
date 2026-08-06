class Solution {
public:
    bool isSimilar(string s, string t) {
        int diff = 0;

        for(int i=0; i<s.length(); i++) {
            if(s[i] != t[i]) {
                diff++;
            }
        }

        return diff == 2 || diff == 0 ;
    }

    void dfs(unordered_map<int, vector<int>> adj, int src, vector<bool>& vis) {
        vis[src] = true ;

        for(auto ngbr : adj[src]) {
            if(!vis[ngbr]) {
                dfs(adj, ngbr, vis) ;
            }
        }
    }
    int numSimilarGroups(vector<string>& strs) {
       int n = strs.size();
        unordered_map<int, vector<int>> adj ;
       for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {

                if(isSimilar(strs[i], strs[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
       } 

        vector<bool> vis(n, false) ;
        int cnt = 0;
        for(int i=0; i<n; i++) {
            if(!vis[i]) {
                dfs(adj, i, vis) ;
                cnt++;
            }
        }

        return cnt ;
    }
};