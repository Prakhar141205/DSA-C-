
class Solution {
public:
    int m, n;

    void dfs(vector<vector<int>>& maze, int i, int j,
             string& temp, vector<string>& ans) {

        if (i < 0 || i >= m || j < 0 || j >= n ||
            maze[i][j] == 0)
            return;

        if (i == m - 1 && j == n - 1) {
            ans.push_back(temp);
            return;
        }

        maze[i][j] = 0;

        // Down
        temp += "D";
        dfs(maze, i + 1, j, temp, ans);
        temp.pop_back();

        // Left
        temp += "L";
        dfs(maze, i, j - 1, temp, ans);
        temp.pop_back();

        // Right
        temp += "R";
        dfs(maze, i, j + 1, temp, ans);
        temp.pop_back();

        // Up
        temp += "U";
        dfs(maze, i - 1, j, temp, ans);
        temp.pop_back();

        maze[i][j] = 1;
    }

    vector<string> ratInMaze(vector<vector<int>>& maze) {

        m = maze.size();

        if (m == 0) return {};

        n = maze[0].size();

        vector<string> ans;
        string temp = "";

        if (maze[0][0] == 0 || maze[m-1][n-1] == 0)
            return ans;

        dfs(maze, 0, 0, temp, ans);

        return ans;
    }
};
