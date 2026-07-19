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
 #include <algorithm>
class Solution {
public:
    int ans = 0;
    void  solve(TreeNode* root, bool isLeft, int curr) {
        if(!root) return ;

        ans = max(curr, ans);

        if(isLeft) {
            solve(root->left, false, curr+1); // right
            solve(root->right, true, 1); // left find another required path
        }else {
            solve(root->right, true, curr+1); // right ==> left
            solve(root->left, false, 1);  // right  ==> right to get better apth
        }

        return ;
    }
    int longestZigZag(TreeNode* root) {
        if(!root) return 0;
       
        solve(root->left, false, 1); // left
        solve(root->right, true, 1); // right

        return ans;
    }
};