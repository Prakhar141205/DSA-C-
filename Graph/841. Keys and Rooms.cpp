class Solution {
public:
    void dfs(vector<vector<int>>& rooms, vector<int>& vis, int src) {
        if(vis[src]) return ;
        vis[src] = 1;

        for(auto& v : rooms[src]) {
            if(!vis[v]) {
                dfs(rooms, vis, v);
            }
        }
        return ;
    }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> vis(n, 0);
        int src = 0;
        dfs(rooms, vis, src);

        for(auto& x : vis) {
            if(x == 0) return false;
        }

        return true;
    }
};

// using bFS

class Solution {
public:
    // void dfs(vector<vector<int>>& rooms, vector<int>& vis, int src) {
    //     if(vis[src]) return ;
    //     vis[src] = 1;

    //     for(auto& v : rooms[src]) {
    //         if(!vis[v]) {
    //             dfs(rooms, vis, v);
    //         }
    //     }
    //     return ;
    // }
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        queue<int> que;
        vector<int> vis(n, 0);
        int src=0;
        que.push(src);
        vis[src] = 1;
        while(que.size()) {
            int u = que.front();
            que.pop();

            for(auto& v : rooms[u]) {
                if(!vis[v]){
                    vis[v] = 1;
                    que.push(v);
                    
                }
            }
        }

        for(int& x : vis) {
            if(x == 0) {
                return false;
            }
        }

        return true;
    }

};