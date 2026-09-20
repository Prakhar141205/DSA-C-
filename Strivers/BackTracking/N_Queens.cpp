class Solution {
public:
    vector<vector<string>> result; 
    int n;
    bool isValid(vector<string>& board, int r, int c) {

        // upward

        for(int i=r; i>=0; i--) {
            if(board[i][c] == 'Q') {
                return false;
            }
        } 

        // right up
        for(int i=r-1, j=c+1; i >= 0 && j < n; i--, j++) {
            if(board[i][j] == 'Q') return false;
        }

        // left up
        for(int i=r-1, j=c-1; i >= 0 && j >= 0; i--, j--) {
            if(board[i][j] == 'Q') return false;
        }

        return true;

    }
    void solve(vector<string>& board, int row) {
        if(row >= n) {
            result.push_back(board);
            return;
        }

        for(int c = 0; c < n; c++) {

            if(isValid(board, row, c)) {
                board[row][c] = 'Q';
                solve(board, row+1);
                board[row][c] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int N) {
        n = N;
        vector<string> board(n, string(n, '.'));
        solve(board, 0);

        return result;
        
    }
};

// improved version 