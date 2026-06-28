class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        // here we will use diagonal traversal technique which is that
        // if you have to travel from top-left to bottom- right use (i - j) {i-j remains same for all these daigonals}
        // if you have to travel from bottom-left to top- right use (i + j) {i+j remains same for all these daigonals}

        unordered_map<int, vector<int>> mp; // (i-j), elements

        // storing the diagonals in the map
        for(int i=0; i<mat.size(); i++){

            for(int j=0; j<mat[i].size(); j++){

                mp[i-j].push_back(mat[i][j]);
            }
        }
        
        // sort the second elements of the map i.e, sort the vector

        for(auto& v : mp){
            sort(v.second.begin(), v.second.end());
        }

        for(int i=mat.size()-1; i>=0; i--){

            for(int j=mat[i].size()-1; j>=0; j--){

                mat[i][j] = mp[i-j].back();
                mp[i-j].pop_back();
            }
        }

        return mat;

    }
};

// inplace sorting
class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
    int n=mat.size();
    int m=mat[0].size();
    for(int k=0;k<n;k++){
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
           if(mat[i-1][j-1]>mat[i][j]){
            swap(mat[i-1][j-1],mat[i][j]);
           }
        }
    }
    }
return mat;
    }
};