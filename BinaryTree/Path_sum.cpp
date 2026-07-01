/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */ 
typedef  TreeNode* tt;
class Solution {
public:

    bool dfs(tt root, int sum, int target){
        if(!root) return false;

        sum += root->val;

        if(sum == target && (!root->left && !root->right)) return true;

        return dfs(root->left, sum, target) || 
                dfs(root->right, sum, target);
    }
    bool hasPathSum(TreeNode* root, int t) {

        if(!root) return false;

        int sum = 0;

        return dfs(root, sum, t);
        
    }
};