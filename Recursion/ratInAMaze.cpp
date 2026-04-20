
// using extra space for the visited matrix
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void helper(vector<vector<int>> &mat, int row, int col, vector<string> &ans, string path, vector<vector<bool>> &vis){
    int n = mat.size();
    if(row < 0 || col < 0 || row >= n || col >= n || mat[row][col] == 0|| vis[row][col]==true){
        return ;
    }

    if(row == n-1 && col == n-1){
        ans.push_back(path);
        return;
    }

    vis[row][col]=true;
    helper(mat, row-1, col, ans, path+"U", vis);
    helper(mat, row+1, col, ans, path + "D", vis);
    helper(mat, row, col+1, ans, path+"R", vis);
    helper(mat, row, col-1, ans, path+"L", vis);

    vis[row][col] = false; // backtrack taki agar kisi aur path ki wajah se true hojaye toh use wapas use false 

}
vector<string> findPath(vector<vector<int>> &mat){
    int n = mat.size();
    vector<vector<bool>> vis(n, vector<bool> (n, false));
    vector<string> ans;
    string path = "";

    helper(mat, 0, 0, ans, path, vis);

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