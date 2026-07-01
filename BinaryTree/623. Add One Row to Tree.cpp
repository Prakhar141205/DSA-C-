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
typedef TreeNode* tt;
class Solution {
public:
    tt solve(tt root, int val, int depth, int curr) {
       if(!root) return root;

        if(curr == depth-1) {
            // store the old root left and right
            tt tempLeft = root->left;
            tt tempright = root->right;

            // add a new row at given depth
            root->left = new TreeNode(val);
            root->right = new TreeNode(val);

            // restore rhe old connectioln
            root->left->left = tempLeft;
            root->right->right = tempright;

            return root;

        }

        solve(root->left, val, depth, curr+1);
        solve(root->right, val, depth, curr+1);

        return root;
    }
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if(depth == 1 ) {
            // tt temp = root;
            tt newNode = new TreeNode(val);

            newNode->left = root;

            return newNode;
        }
        int curr = 1;

        return solve(root, val, depth, curr);

        
        
    }
};