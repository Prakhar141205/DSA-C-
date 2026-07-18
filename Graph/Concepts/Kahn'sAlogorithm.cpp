class Solution {
public:
    bool isCycleBFS(unordered_map<int, vector<int>>& adj, int n,vector<int>& inDegree) {
        queue<int> que;
        int cnt=0; // no of nodes that visited
        // push all the vertices with indegree equal 0 
        for(int i=0; i< n; i++) {
            if(inDegree[i] == 0) {
                cnt++;
                que.push(i);
            }
        }

        while(!que.empty()) {
            int u = que.front();
            que.pop();

            for(auto& v : adj[u]) {
                inDegree[v]--;
                if(inDegree[v] == 0) {
                    cnt++;
                    que.push(v);
                }
            }
        }

        if(cnt == n) return true;
        return false;
    }
    bool canFinish(int n, vector<vector<int>>& courses) {
        unordered_map<int, vector<int> > adj;
        vector<int> inDegree(n);
        for(auto& course : courses) {
            int dest = course[0];
            int src = course[1];
            adj[src].push_back(dest);
            inDegree[dest]++;
        }
        

        
        return isCycleBFS(adj, n, inDegree);
        
    }
};

// 
#include <iostream>
#include<unordered_map>
#include <vector>
#include <queue>
using namespace std;

class Graph{
public:
    vector<int> kahnAlgorithm(vector<vector<int>>& adj) {
        int V = adj.size();

        vector<int> inDegree(V, 0);
        for(int u=0; u<V; u++) {
            for(auto& x : adj[u]) {
                inDegree[x]++;
            }
        }

        queue<int> que;
        // to 
        for(int i=0; i<V; i++) {
            if (inDegree[i] == 0) que.push(i);
        }

        
        vector<int> res;

        while(!que.empty()) {
            int u = que.front();
            que.pop();
            res.push_back(u);

            for(int& ngbr : adj[u]) {
                inDegree[ngbr]--;
                if(inDegree[ngbr] == 0) {
                    que.push(ngbr);

                }
            }
        }
        return res;
    }
};
int main(){
    // make an adjaceny list 
    vector<vector<int>> adj = {{2, 3}, {4}, {3, 1}, {1}, {}, {1, 4}};
    Graph graph;
    vector<int> res = graph.kahnAlgorithm(adj);

    for(int x :  res) cout << x << " ";
    return 0;
}