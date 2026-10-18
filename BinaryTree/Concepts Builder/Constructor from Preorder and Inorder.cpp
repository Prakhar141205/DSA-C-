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
    int n ;
    int getIdx(vector<int>& inorder, int ele) {
        int idx = -1;
        for(int i=0; i<n; i++) {
            if(inorder[i] == ele) {
                idx = i;
                break;
            }
        }

        return idx;
    }
    int i = 0;
    TreeNode* solve(int l, int r, vector<int>& preorder, vector<int>& inorder) {
        if(l > r) return nullptr;
        int root_val = preorder[i++];

        TreeNode* root = new TreeNode(root_val);
        int idx = getIdx(inorder, root_val);

        root->left = solve(l, idx-1, preorder, inorder);
        root->right = solve(idx+1, r, preorder, inorder);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        n = preorder.size();
        return solve(0, n-1, preorder, inorder);
    }
};