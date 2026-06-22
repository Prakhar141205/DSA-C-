class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return nullptr;
        
        if(root == p || root == q) return root;

        TreeNode* leftNode = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightNode = lowestCommonAncestor(root->right, p, q);
        
        if(leftNode && rightNode)  return root;

        return !leftNode ? rightNode : leftNode;
    }
};