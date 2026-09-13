class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        map<int, vector<int>> mp;

        for(int i=0; i<mat.size(); i++){

            for(int j=0; j<mat[i].size(); j++){

                mp[i+j].push_back(mat[i][j]);
            }
        }

        vector<int> ans;
        bool flip = true;
        for(auto& p : mp){
            if(flip){
                reverse(p.second.begin(), p.second.end());
            }
            for(int& x : p.second){
                ans.push_back(x);
            }

            flip = !flip;
        }
        return ans;
    }
};