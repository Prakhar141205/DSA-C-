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

    bool isCycleDirHelperDFS(int src, vector<bool> &vis, vector<bool> &recPath){
        vis[src]=true;
        recPath[src]=true;

        for(int v : l[src]){
            if(!vis[v]){
                if(isCycleDirHelperDFS(v, vis, recPath)) return true;
            }else if(recPath[v]) // visited hai aur recursion path me bhi hai => cycle exists
                return true;
        }

        recPath[src]=false;
        return false;
    }
    bool isCycleDirDFS(){
        int src = 0;
        vector<bool> vis(V, false);
        vector<bool> recPath(V, false);

        for(int i=0; i<V; i++){
            if(!vis[i]){
                if(isCycleDirHelperDFS(i, vis, recPath)) return true;
            }
        }
        return false;
    }

};



int main(){
    Graph g(4, false);

    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
   
    cout << g.isCycleDirDFS();
    return 0;
}