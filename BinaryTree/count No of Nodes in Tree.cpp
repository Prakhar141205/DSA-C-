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


//  TC: O(less than n)
class Solution {
public:
    // for perfect binary tree no of nodes == 
    int countNodes(TreeNode* root) {
        if(!root) return 0;

        int leftCount = countNodes(root->left);
        int rightCount = countNodes(root->right);

        if(leftCount == rightCount) { // from here the tree is perfect binary tree i.e, leftheight == rightHeight
            return pow(2, max(leftCount, rightCount) + 1) - 1 ;
        }

        return leftCount + rightCount + 1;
        
    }
};