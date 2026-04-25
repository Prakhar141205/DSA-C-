#include <iostream>
#include <vector>

void printSudoko(int arr[9][9]){
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool isSafe(int sudoko[9][9], int row, int col, int digit){
    for(int i=0; i<9; i++){
        if(sudoko[i][col] == digit){
            return false;
        }
    }

    for(int i=0; i<9; i++){
        if(sudoko[row][i] == digit){
            return false;
        }
    }

    // grid

    int srow = (row/3)*3;
    int scol = (col/3)*3;

    for(int i=srow; i<srow+3; i++){
        for(int j=scol; j<scol+3; j++){
        if(sudoko[row][col] == digit){
            return false;
        }           
        }
    }
    return true;
}

bool sudokoSolver(int sudoko[9][9], int row, int col){

    if(row == 9){
        printSudoko(sudoko);
        return true;
    }
    int nextRow = row;
    int nextCol = col+1;

    if(nextCol == 9){
        nextRow = row+1;
        nextCol=0;
    }

    if(sudoko[row][col] != 0){
        return sudokoSolver(sudoko, nextRow, nextCol);
    }

    for(int i=1; i<=9; i++){ // i => digit to be placed
        if(isSafe(sudoko,  row,  col,  i)){
            sudoko[row][col] = i;
            if(sudokoSolver(sudoko, nextRow, nextCol)) return true;
            sudoko[row][col] = 0; // backtrack

        }
    }
    return false;
}
int main(){
    int sudoko[9][9] = {{0, 0, 8, 0, 0, 0, 0, 0, 0},
                        {4, 9, 0, 1, 5, 7, 0, 0, 2},
                        {0, 0, 3, 0, 0, 4, 1, 9, 0},
                        {1, 8, 5, 0, 6, 0, 0, 2, 0},
                        {0, 0, 0, 0, 2, 0, 0, 6, 0},
                        {9, 6, 0, 4, 0, 5, 3, 0, 0},
                        {0, 3, 0, 0, 7, 2, 0, 0, 4},
                        {0, 4, 9, 0, 3, 0, 0, 5, 7},
                        {8, 2, 7, 0, 0, 9, 0, 1, 3}};
   
    sudokoSolver(sudoko, 0, 0);
    return 0;
}