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
    typedef TreeNode* tn;

    tn deleteNodes(tn root, unordered_set<int>& st, vector<tn>& result){

        if(!root) return root;
        // heere we need to use bottom up using DFS because if we use top down than may be we could lost the access of other node that later we have to delete

        root->left = deleteNodes(root->left, st, result);
        root->right = deleteNodes(root->right, st, result);

        if(st.find(root->val) != st.end()){
            if(root->left) result.push_back(root->left);
            if(root->right) result.push_back(root->right);

            // after inserting the left and right tree
            // now we can delete the current root node
            return nullptr;
        }
        return root; // agar node delete na krni ho means it is not in set 

    }
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<tn> result;

        unordered_set<int> st(to_delete.begin(), to_delete.end());

        deleteNodes(root, st, result);
        
        // check whether we have to delete the root node or not
        // as we ve only considered the left and right subtree in the deleteNodes finction

        if(st.find(root->val) == st.end()){ // root node need not to be deleted
            result.push_back(root);
        }
        return result;
        
    }
};