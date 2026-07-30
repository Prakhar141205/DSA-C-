
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {

        if(!root) return {};

        queue<TreeNode*> que;
        que.push(root);
        vector<int> ans; 
        while(!que.empty()) {
            int n = que.size();
            int lev_max = INT_MIN;
            while(n--) {
                auto curr = que.front() ;
                que.pop();

                lev_max = max(curr->val, lev_max);

                if(curr->left) que.push(curr->left);
                if(curr->right) que.push(curr->right) ;
            }
            ans.push_back(lev_max) ;
        }
        
        return ans ;
    }
};

// using DFS 

    void dfs(TreeNode* root, vector<int>& res, int depth) {
        if(!root ) return;

        if(res.size() == depth) {
            res.push_back(root->val);
        }else {
            res[depth] = max(root->val, res[depth]) ;
        }

        dfs(root->left, res, depth + 1);
        dfs(root->right, res, depth + 1);
    }
    vector<int> largestValues(TreeNode* root) {
        if(!root) return {} ;
        int depth = 0 ;

        vector<int> res ;
        dfs(root, res, depth);

        return res ;
    }