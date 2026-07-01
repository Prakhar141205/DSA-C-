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
class Solution {   // curr => &ref karna reh gaya tha
public:
    void check(TreeNode* &root,int sum,int targetSum,vector<int> &curr,vector<vector<int>> &ans) {
        if(root == NULL) return;
        
        sum += root-> val; curr.push_back(root-> val);
        if(root-> left == NULL && root-> right == NULL) {
            if(sum == targetSum) ans.push_back(curr); 
            curr.pop_back();
            return;
        }
        
        check(root-> left, sum, targetSum, curr, ans);
        check(root-> right, sum, targetSum, curr, ans);
        curr.pop_back();
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if(root == NULL) return {};

        vector<vector<int>> ans; vector<int> curr; int sum = 0;
        check(root, sum, targetSum, curr, ans);
        return ans;
    }
};