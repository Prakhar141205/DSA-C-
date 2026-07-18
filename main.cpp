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