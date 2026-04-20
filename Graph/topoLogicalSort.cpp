#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <stack>
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

    void topoSortHelper(int src, vector<bool> &vis, stack<int> &s){
        vis[src] = true;

        for(int v : l[src]){
            if(!vis[v]) topoSortHelper(v, vis, s); 
        }
        s.push(src);
    }

    void topoSort(){
        vector<bool> vis(V, false);
        stack<int> s;

        for(int i=0; i<V; i++){
            if(!vis[i]){
                topoSortHelper(i, vis, s);
            }
        }

        while(s.size() > 0){
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    }
};



int main(){
    Graph g(6, false);

    g.addEdge(3, 1);
    g.addEdge(2, 3);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(5, 0);
    g.addEdge(5, 3);
   
    g.topoSort();
    return 0;
}