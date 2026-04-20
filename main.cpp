// without using extra space for visited matrix
// TC O(4 to the power n square)

// we have n square cells and for each cell we have 4 options
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void helper(vector<vector<int>> &mat, int row, int col, vector<string> &ans, string path){
    int n = mat.size();
    if(row < 0 || col < 0 || row >= n || col >= n || mat[row][col] == 0||mat[row][col] == -1){
        return ;
    }

    if(row == n-1 && col == n-1){
        ans.push_back(path);
        return;
    }

    mat[row][col]=-1; // visit

    helper(mat, row-1, col, ans, path+"U");
    helper(mat, row+1, col, ans, path + "D");
    helper(mat, row, col+1, ans, path+"R");
    helper(mat, row, col-1, ans, path+"L");

    mat[row][col] = 1; // unvisit
    // backtrack taki agar kisi aur path ki wajah se true hojaye toh use wapas use false 

}
vector<string> findPath(vector<vector<int>> &mat){
    int n = mat.size();
    
    vector<string> ans;
    string path = "";

    helper(mat, 0, 0, ans, path);

    return ans;
}
int main(){
    vector<vector<int>> mat = {{1, 0, 0, 0}, {1, 1, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 1}};
    vector<string> ans=findPath(mat);
    
    for(string s : ans){
        cout << s << "\n";
    }

    cout << endl;
    return 0;   
}