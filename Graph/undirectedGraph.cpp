#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
using namespace std;

class Graph{
public:
    int V;
    list<int>* l;
    bool  isUndir;


    Graph(int V, bool isUndir = true){
        this->V = V;
        this->isUndir = isUndir;
        l = new list<int> [V];
    }


    void addEdge(int u, int v){
        
        l[u].push_back(v);
        
        if(isUndir)  l[v].push_back(u);
    }

    void print(){
        
        for(int i=0; i<V; ++i){
            cout << i << "->";
            for(int x : l[i]){
                cout << x <<" ";
            } 
            cout << endl;
        }
    }

    void BFSTraversal(int src){
    vector<bool> vis(V, false);
    queue<int> q;
    q.push(src);
    vis[src]=true;
    while(q.size()){
        int u = q.front();
        q.pop();

        cout << u << " ";
        for(int v : l[u]){
            if(!vis[v]){
                vis[u]=true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

    void dfsHelper(int src,vector<bool> vis){

        cout << src << " ";
        vis[src]=true;

        for(int v : l[src]){
            if(!vis[v]){
                dfsHelper(v, vis);
            }
        }
        
    }
    void dfs(){
        int src = 0;
        vector<bool> vis(V, false);

        return dfsHelper(src, vis);
    }

    bool isCycleHelper(int src, int par, vector<bool> &vis){
        vis[src]=true;

        for(int u : l[src]){
            if(!vis[u]){
                if(isCycleHelper(u, src, vis)) return true;
            }else if(par != u){
                return true;
            }
        }
        return false;
    }
    bool isCycle(){
        int src = 0;
        vector<bool> vis(V, false);

        for(int i=0; i<V; i++){
            if(!vis[i]){
                if(isCycleHelper(i, -1, vis)) return true;
            }
        }
        return false;
    }

    bool isCycleHelperBFS(int src,vector<bool> &vis){
        queue<pair<int, int>> q; // src, par

        q.push({src, -1});

        while(q.size()){
            int u = q.front().first;
            int par = q.front().second;
            q.pop();
            for(int v : l[u]){
                if(!vis[v]){
                    vis[v]=true;
                    q.push({v, u});
                }else if(par != v){
                    return true;
                }
            }
        }
        return false;
    }

    bool isCycleBFS(){
        int src=0;
        vector<bool> vis(V, false);
        
        for(int i=0; i<V; i++){
            if(!vis[i]){
                if(isCycleHelperBFS(src, vis)) return true;
            }
        }
       return false;  
    }
};



int main(){
    Graph g(5);

    g.addEdge(1, 2);
    g.addEdge(0, 1);
    g.addEdge(2, 4);
    g.addEdge(1, 3);
   
    cout << g.isCycleBFS();
    return 0;
}