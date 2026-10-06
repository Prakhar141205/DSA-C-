
class Solution {
public:
    unordered_map<int, int> mp; // node-- depth
    int maxD = 0;

    void depth(TreeNode* root, int d) {
        if(!root) return;

        maxD = max(maxD, d);
        mp[root->val] = d;

        depth(root->left, d+1);
        depth(root->right, d+1); 
    }

    TreeNode* LCA(TreeNode* root) {
        if(!root || mp[root->val] == maxD) return root;

        TreeNode* l = LCA(root->left);
        TreeNode* r = LCA(root->right);
 
        if(l && r) return root; // left and right both are not null means current root is LCA

        return l != nullptr ? l : r;
    } 
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        
        depth(root, 0);

        return LCA(root);
    }
};


// One pass solution
class Solution {
public:
    pair<int, TreeNode* > solve(TreeNode* root) {
        if(!root ) return {0, NULL};

        auto  l = solve(root->left);
        auto r = solve(root->right);

        if(l.first == r.first ) return {l.first+1, root}; // if depth is same then current root is LCA of deepest leaves
        else if(l.first > r.first) return {l.first+1, l.second}; // if left depth is greater then return left node
        else
        return {r.first+1, r.second}; // if right depth is greater then return right node 
     }
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        return solve(root).second;
    }
};