class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> res;
        for(int ball=0; ball < n; ball++){

            int row=0;
            int col=ball;
            bool isStucked = false;
            while(row < m && col < n){
                
                if(grid[row][col] == 1){

                    if(col == n-1 || grid[row][col+1] == -1){
                        isStucked = true;
                        break;

                    }

                    col++;
                }else{

                    if(col == 0 || grid[row][col-1] == 1){
                        isStucked = true;
                        break;
                    }
                    col--;
                }

                row++;
            }

            if(isStucked) res.push_back(-1);
            else res.push_back(col);

        }

        return res;
    }
};