class Solution {
public:
    vector<int> lastVisitedCell(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        auto isInvalid = [&](int i, int j) {
            return i < 0 || j < 0 || i >=m || j >= n ;
        } ;

        vector<vector<bool>> vis(m, vector<bool> (n, false));
        int i=0, j=0; 
        vis[0][0] = true;
        while(true) {
            char dir = grid[i][j] ;
            int oi = i;
            int oj = j;
            if(dir == 'L') j--;
            else if(dir == 'R') j++;
            else if(dir == 'U') i--;
            else if(dir == 'D') i++;

            if(isInvalid(i, j) || vis[i][j]) return {oi, oj};

           
            vis[i][j] = true;
        }

        return  {i, j} ;
    }
};