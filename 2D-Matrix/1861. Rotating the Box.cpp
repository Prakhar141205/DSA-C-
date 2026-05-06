class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        vector<vector<char>> verticalGrid(boxGrid[0].size(), vector<char>(boxGrid.size(), '.'));
        for (int i = 0; i < boxGrid.size(); i ++) {
            int stone_num = 0;
            int vertical_i = boxGrid.size() - 1 - i;
            for (int j = 0; j < boxGrid[0].size(); j ++) {
                if (boxGrid[i][j] == '#') {
                    stone_num ++;
                } else if (boxGrid[i][j] == '*') {
                    verticalGrid[j][vertical_i] = '*';
                    int m = j - 1;
                    while (stone_num > 0) {
                        verticalGrid[m][vertical_i] = '#';
                        m --;
                        stone_num --;
                    }
                }
            }

            int m = boxGrid[0].size() - 1;
            while (stone_num > 0) {
                verticalGrid[m][vertical_i] = '#';
                m --;
                stone_num --;
            }
        }

        return verticalGrid;
    }
};

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size(), n = boxGrid[0].size();
        vector<vector<char>> res(n, vector<char>(m, '.'));

        for(int i{0}; i < m; ++i){
            int c = m - 1 - i;
            int empty = -1;
            for(int j{n-1}; j > -1; --j){
                if( boxGrid[i][j] == '*') {res[j][c] = '*'; empty = -1;}
                else if ( boxGrid[i][j] == '.'){
                    if(empty == -1) empty = j;
                }
                else{
                    if(empty == -1) res[j][c] = '#';
                    else{
                        res[empty][c] = '#';
                        empty -= 1;
                    }
                }
            }
        }
        return res;
    }
};


class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size();
        int n = box[0].size();
        vector<vector<char>> result(n, vector<char>(m, '.'));

        // Apply gravity to let stones fall to the lowest possible empty cell in
        // each column
        for (int i = 0; i < m; i++) {
            int lowestRowWithEmptyCell = n - 1;
            // Process each cell in row `i` in reversed order
            for (int j = n - 1; j >= 0; j--) {
                // Found a stone - let it fall to the lowest empty cell
                if (box[i][j] == '#') {
                    // Place it in the correct position in the rotated grid
                    result[lowestRowWithEmptyCell][m - i - 1] = '#';
                    // (Optional - already initialized to '.') result[j][m - i -
                    // 1] = '.';
                    lowestRowWithEmptyCell--;
                }
                // Found an obstacle - reset `lowestRowWithEmptyCell` to the row
                // directly above it
                if (box[i][j] == '*') {
                    // Place the obstacle in the correct position in the rotated
                    // grid
                    result[j][m - i - 1] = '*';
                    lowestRowWithEmptyCell = j - 1;
                }
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();

        // Step 1: Apply gravity
        for (int i = 0; i < m; i++) {
            int empty = n - 1; // position where stone falls
            
            for (int j = n - 1; j >= 0; j--) {
                if (boxGrid[i][j] == '*') {
                    empty = j - 1; // reset after obstacle
                } 
                else if (boxGrid[i][j] == '#') {
                    swap(boxGrid[i][j], boxGrid[i][empty]);
                    empty--;
                }
            }
        }

        // Step 2: Rotate 90° clockwise
        vector<vector<char>> ans(n, vector<char>(m));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ans[j][m - 1 - i] = boxGrid[i][j];
            }
        }

        return ans;
    }
};

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int row = boxGrid.size();
        int col = boxGrid[0].size();

        vector<vector<char>> rotatedGrid(col, vector<char>(row, ' '));

        for(int k=0; k<row; k++){

            int i = col-2;
            int j = col-1;

            while(i>=0){
                // Empty
                if(boxGrid[k][i] == '.'){
                    if(boxGrid[k][j] != '.'){
                        j=i;
                    }
                }
                //Obstacle
                else if(boxGrid[k][i] == '*'){
                    j=i;
                } 
                // Stone
                else{
                    if(boxGrid[k][j]=='.'){
                        boxGrid[k][j] = '#';
                        boxGrid[k][i] = '.';
                        while(boxGrid[k][j] != '.'){
                            j--;
                        }
                    }
                }
                i--;
            }

        }
        // Row = cols
        for(int r=0; r<row; r++){
            for(int c=0; c<col; c++){
                rotatedGrid[c][row-r-1] = boxGrid[r][c];
            }
        }
        
        return rotatedGrid;

    }
};

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int row = boxGrid.size();
        int col = boxGrid[0].size();
        vector<vector<char>> result(col, vector<char>(row,'.'));
        for (int r = 0; r < row; r++) {
            int i = col - 1;
            for (int c = col - 1; c >= 0; c--) {
                if (boxGrid[r][c] == '#') {
                    result[i][row - r - 1] = '#';
                    i--;
                }
                else if (boxGrid[r][c] == '*') {
                    result[c][row - r - 1] = '*';
                    i = c - 1;
                }
            }
        }
        return result;
    }
};

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int n = boxGrid.size(), m = boxGrid[0].size(), count = 0;
        vector<vector<int>> pos_count;
        for (int i = 0; i < n; i++) {
            count = 0;
            for (int j = 0; j <= m; j++) {
                if (j == m || boxGrid[i][j] == '*') {
                    pos_count.push_back({i, j, count});
                    count = 0;
                    continue;
                }
                if (boxGrid[i][j] == '#') {
                    count++;
                }
            }
        }

        vector<vector<char>> boxGrid90(m, vector<char>(n, '.'));

        for (auto x : pos_count) {
            int i = x[0], j = x[1], count = x[2];

            if (j != m) {
                boxGrid90[j][n - i - 1] = '*';
            }

            for (int k = j - 1; k >= j - count; k--) {
                boxGrid90[k][n - i - 1] = '#';
            }
        }

        return boxGrid90;
    }
};