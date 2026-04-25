#include <iostream>
#include <vector>

void printBoard(std::vector<std::vector<char>> board){
    int n = board.size();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            std::cout << board[i][j] <<" ";

        }
        
        std::cout << std::endl;
        
    }
    std::cout << "------------------------------------------------->\n";
}


bool isSafe(std::vector<std::vector<char>> &board, int row, int col, int n){
    
    // horizontal
    for(int i=0; i<n; i++){
        if(board[row][i] == 'Q'){
            return false;
        }
    }

    // vertical
    for(int i=0; i<n; i++){
        if(board[i][col] == 'Q'){
            return false;
        }
    }

    // right diagonal 
    for(int i=row, j=col; i>=0 && j<n; i--,j++ ){
        if(board[i][j] == 'Q'){
            return false;
        }
    }

    // left diagonal
    for(int i=row, j=col; i>=0 && j>=0; i--,j-- ){
        if(board[i][j] == 'Q'){
            return false;
        }
    }
    return true;
}

void nQueens(std::vector<std::vector<char>> &board, int row, int n){
    if(row == n){
        printBoard(board);
        
        return;
    }
    
    for(int i=0; i<n; i++){
        if(isSafe(board, row, i, n)){
            board[row][i] = 'Q';
            nQueens(board, row+1, n);
            board[row][i] = '.';
        }
    }
}
int main(){
    std::vector<std::vector<char>> board;

    int n = 4;

    for(int i=0; i<n; i++){
        std::vector<char> newRow;

        for(int j=0; j<n; j++){
            newRow.push_back('.');
        }
        board.push_back(newRow);
    }

   nQueens(board, 0, n);
    return 0;
}