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
    int level[100001];
    int height[100001];
    int levelMaxHeight[100001];
    int levelSecMaxHeight[100001];
    int findHeight(TreeNode* root , int l) {
        if(!root) return 0;

        level[root->val] = l;
        height[root->val] = max(findHeight(root->left, l+1), findHeight(root->right, l+1)) + 1 ;

        if(levelMaxHeight[l] < height[root->val]) {
            levelSecMaxHeight[l] = levelMaxHeight[l];
            levelMaxHeight[l] = height[root->val];
        } else if(levelSecMaxHeight[l] < height[root->val]) {
            levelSecMaxHeight[l] = height[root->val];
        }
        return height[root->val];
    }
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        findHeight(root, 0);

        vector<int> result;

        for(int& node: queries) {
            int L = level[node];
            int H = (levelMaxHeight[L] == height[node]) ? levelSecMaxHeight[L] : levelMaxHeight[L] ;

            int tempRes = L+H-1;
            result.push_back(tempRes);
        }

        return result;
    }
};