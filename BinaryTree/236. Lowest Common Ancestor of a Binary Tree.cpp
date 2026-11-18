
/****************************************************** C++ ***************************************************/
//Approach - Use DFS and find
//T.C : O(n)
//S.C : O(n) for System Stack used for Recursion
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)
            return NULL;
        
        if(root->val == p->val || root->val == q->val)
            return root;
        
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        
        if(l && r)
            return root;
        
        return l?l:r;
    }
};


class Solution {
public:
    bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
        if (!root) return false;

        path.push_back(root);

        if (root == target)
            return true;

        if (findPath(root->left, target, path) ||
            findPath(root->right, target, path)) {
            return true;
        }

        path.pop_back();
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path1, path2;

        findPath(root, p, path1);
        findPath(root, q, path2);

        TreeNode* lca = nullptr;

        int i = 0;
        while (i < path1.size() && i < path2.size() &&
               path1[i] == path2[i]) {
            lca = path1[i];
            i++;
        }

        return lca;
    }
};