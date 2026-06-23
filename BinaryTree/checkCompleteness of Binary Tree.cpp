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
    // using BFS
    // bool isCompleteTree(TreeNode* root) {
    //     if(!root) return true;

    //     queue<TreeNode*> q;
        
    //     bool pastNode = false; // track whether the past Node is null or not
    //     q.push(root);

    //     while(!q.empty()){
    //         TreeNode* currNode = q.front();
    //         q.pop();

    //         if(currNode == NULL){
    //             pastNode = true;
    //         }else{
    //             if(pastNode == true){
    //                 return false;
    //             }

    //             q.push(currNode->left);
    //             q.push(currNode->right);
    //         }
    //     }

    //     return true;
        
    // }
    // using DFS
    // logic: represent tree into array form
    // index > total no of nodes => not a complete binary tree for 1 based indexing array


    // using DFs
    int totalNodes(TreeNode* root){
        if(!root) return 0;

        int leftNodes = totalNodes(root->left);
        int rightNodes = totalNodes(root->right);

        return leftNodes + rightNodes + 1;
    }

    bool dfs(TreeNode* root, int total_nodes, int i){
        if(!root) return true;

        if(total_nodes <= i){
            return false;
        }

        return  dfs(root->left, total_nodes, 2*i+1)
                && dfs(root->right, total_nodes, 2*i+2);
    }
    bool isCompleteTree(TreeNode* root) {
        if(!root) return true;

        int total_nodes = totalNodes(root);
        int i = 0;
        return dfs(root, total_nodes, i);
        
    }
};