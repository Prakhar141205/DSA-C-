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
class Solution {
public:
    int cnt = 0;
    int dfs(TreeNode* root) {
         if(!root) return INT_MIN;

        
        int left = dfs(root->left);
        int right = dfs(root->right);
        int csm = max({root->val, left, right});
        
        if(root->val == csm) {
            cout << root->val << " ";
            cnt++;
        }
        
        return csm;
    }
    int countDominantNodes(TreeNode* root) {
        if(!root) return 0;

        dfs(root);
        return cnt;
    }
};