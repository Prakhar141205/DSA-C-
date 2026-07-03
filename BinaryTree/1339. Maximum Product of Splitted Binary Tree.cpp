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

 typedef TreeNode* tt;
 typedef long long ll;
class Solution {
public: 
    int mod = 1e9+7;
    ll totSum;
    ll ans=0;
    int totalSum(tt root) {
        if(!root) return 0;

        return totalSum(root->left)
              + totalSum(root->right) + root->val;
    }
    
    
    int solve(tt root) {
        if(!root) return 0;

        
        ll subTreeSum = root->val + solve(root->left) + solve(root->right);

        ll remSum = totSum - subTreeSum ;

        ans = max(ans, remSum*subTreeSum);


        return subTreeSum;
    }


    int maxProduct(TreeNode* root) {
        if(!root) return 0;

        totSum = totalSum(root);
        cout << totSum << " ";
        solve(root);

        return ans%mod;

        
    }
};