// Brute force:
// select one root to be the ancestor, then traverse the tree to find the maximum difference between the ancestor and its descendants.

class Solution {
public:
    typedef TreeNode* tt;
    int maxDiff  = -1;
    void helper(tt root, tt child) {
        if(!child) return;

        maxDiff = max(maxDiff, abs(root->val - child->val));

        helper(root, child->left);
        helper(root, child->right);

    }
    int maxAncestorDiff(TreeNode* root) {
        if(!root) return 0;

        helper(root, root->left);
        helper(root, root->right);

        maxAncestorDiff(root->left);
        maxAncestorDiff(root->right);


        return maxDiff;
        
    }
};


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
    typedef TreeNode* tt;
    int helper(tt root, int minv, int maxv) {
        if(!root) return abs(minv - maxv);

        minv = min(minv, root->val);
        maxv = max(maxv, root->val);

        int leftMax = helper(root->left, minv, maxv);
        int rightMax = helper(root->right, minv, maxv);

        return max(leftMax, rightMax);


    }
    int maxAncestorDiff(TreeNode* root) {
        if(!root) return 0;

        return helper(root, root->val, root->val);
        
    }
};