class Solution {
public:
    
    TreeNode* makeTree(vector<int>& preorder, vector<int>& inorder, int st, int end, int& idx){
        if(st > end ) return nullptr;

        int root_val = preorder[idx];

        int i = st;

        for(; i<=end; i++){
            if(root_val == inorder[i]) break;

        }

        idx++;

        TreeNode* root = new TreeNode(root_val);
        root->left = makeTree(preorder, inorder, st, i-1, idx);
        root->right = makeTree(preorder, inorder, i+1, end, idx);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();

        int idx=0;

        return makeTree(preorder, inorder, 0, n-1, idx);
        
    }
};