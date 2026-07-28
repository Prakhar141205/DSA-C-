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
    typedef unsigned long long ll;
    int widthOfBinaryTree(TreeNode* root) {
        deque<pair<TreeNode*, ll>> que;
        que.push_back({root, 0});
        int ans = 0;
        while(!que.empty()) {

                int n = que.size();
                auto [currNode, idx] = que.front() ;
                auto [node, idx_back] = que.back();
                ans = max<ll>(ans, ( idx_back - idx  + 1));
            while(n--){
                auto [currNode, idx] = que.front() ;
                que.pop_front();
                if(currNode->left) que.push_back({currNode->left, 2*idx+1});
                if(currNode->right) que.push_back({currNode->right, 2*idx+2});
            }
        
        }

        return ans ;
    }
};