class Solution {
  public:
    vector<string> res;
    int n ;
    void dfs(vector<vector<int>>& maze, int i, int j, string& path) {
        
        if(i < 0 || j< 0 || i >= n || j >= n || maze[i][j] == 0) return ;
        
        if(i == n-1 && j == n-1) res.push_back(path);
        
        maze[i][j] = 0 ; //marks visisted
        
        path.push_back('L');
        dfs(maze, i, j-1, path);
        path.pop_back();
        
        path.push_back('D');
        dfs(maze, i+1, j, path);
        path.pop_back();
        
        path.push_back('R');
        dfs(maze, i, j+1, path);
        path.pop_back();
        
        path.push_back('U');
        dfs(maze, i-1, j, path);
        path.pop_back();
        
        maze[i][j] = 1 ; // backtracking 
    }
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        string path = "";
        n = maze.size();
        dfs(maze, 0, 0, path);
        
        return res;
    }
};