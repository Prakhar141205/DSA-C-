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
    vector<TreeNode*> solve(int start, int end) {
        if(start > end) return {nullptr} ;
        if(start == end) {
            TreeNode* root = new TreeNode(start) ;
            return {root} ;
        }

        vector<TreeNode*> res ;
        for(int i=start; i <= end; i++) {
            vector<TreeNode*> left_bsts = solve(start, i-1);
            vector<TreeNode*> right_bsts = solve(i+1, end);

            for(auto left : left_bsts) {
                for(auto right : right_bsts) {

                    TreeNode* root = new TreeNode(i);
                    root->left = left ;
                    root->right = right ;

                    res.push_back(root);
                }
            }
        }

        return res ;
    }
    vector<TreeNode*> generateTrees(int n) {
        if(n == 1) return vector<TreeNode*> {new TreeNode(1)} ;

        return solve(1, n) ;
    }
};