// using level order traversal
// using BFS
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(!root) return {};
        queue<TreeNode*> q;

        q.push(root);
        int temp = -10000;
        while(!q.empty()){
            int n = q.size();

            while(n--){
                TreeNode* curr = q.front();
                q.pop();
                temp =  curr->val;
                // make sure to insert the left child first 
                // if push right child first you will get the left side view of tree
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            
            ans.push_back(temp);

        }


        return ans;
    }
};

// using DFS

class Solution {
public:
    void preOrder(TreeNode* root, int level, vector<int>& res){
        if(!root) return;

        if(res.size() < level){
            res.push_back(root->val);
        }

        if(root->right) preOrder(root->right, level+1, res);
        if (root->left) preOrder(root->left, level+1, res);
    }
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return {};
        vector<int> res;
        preOrder(root, 1, res);
        
        return res;
    }
};