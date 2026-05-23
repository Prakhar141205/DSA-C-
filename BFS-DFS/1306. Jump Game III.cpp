// simple DFS

class Solution {
public:
    bool dfs(vector<int> arr, int curr, vector<bool> &vis){
        
        if(arr[curr] == 0) return true; // reach the destination
        int n = arr.size();
        vis[curr] = true;

        int rightJump = curr + arr[curr];
        int leftJump = curr - arr[curr];

        if(leftJump >= 0 && !vis[leftJump]){
            if(dfs(arr, leftJump, vis)) return true;
        }

        if(rightJump < n && !vis[rightJump]){
            if(dfs(arr, rightJump, vis)) return true;
        }

        return false;
    }
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> vis(n, false);

        return dfs(arr, start, vis);
    }
};

// Clean DFS

class Solution {
public:
    bool dfs(vector<int> arr, int curr, vector<bool> &vis){
        int n = arr.size();

        if(curr < 0 || curr  > n) return false; // invalid left and right jump

        if(arr[curr] == 0) return true; // reach the destination
        
        if(!vis[curr]) return false;

        vis[curr] = true;

        return (dfs(arr, curr - arr[curr], vis)) ||
                (dfs(arr, curr + arr[curr], vis));
    }
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> vis(n, false);

        return dfs(arr, start, vis);
    }
};

// using bfs

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();

        queue<int> q;

        vector<bool> vis(n, false);

        q.push(start);
        vis[start]=true;

        while(!q.empty()){
            int curr = q.front();
            q.pop();
            if(arr[curr] == 0) return true;
            int rightJump = curr + arr[curr];
            int leftJump = curr - arr[curr];

            if(leftJump >= 0 && !vis[leftJump]){
                q.push(leftJump);
                vis[leftJump] = true;
            }

            if(rightJump < n && !vis[rightJump]){
                q.push(rightJump);
                vis[rightJump] = true;
            }
        }
        return false;
    }
};

// SInce array contain the non negative integer hence we use the array as visited

class Solution {
public:
    bool dfs(vector<int> arr, int curr, vector<bool> &vis){
        int n = arr.size();

        if(curr < 0 || curr  > n) return false; // invalid left and right jump

        if(arr[curr] == 0) return true; // reach the destination
        
        if(vis[curr] < 0 ) return false;

        vis[curr] = -curr;

        return (dfs(arr, curr - abs(arr[curr]), vis)) ||
                (dfs(arr, curr + abs(arr[curr]), vis));
    }
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        vector<bool> vis(n, false);

        return dfs(arr, start, vis);
    }
};

// final MOst cleaned solution

bool canReach(vector<int>& arr, int start) {
    if(start < 0  || start > n || arr[start] < 0) return false;

    if(arr[start] == 0) return true;

    arr[start] = -start; // marks visited

    return canReach(arr, start - abs(arr[start])) || canReach(arr, start + abs(arr[start])); // canReachLeft || canReachRight

}