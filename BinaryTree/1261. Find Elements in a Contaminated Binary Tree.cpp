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
class FindElements {
public:

    unordered_set<int> st; 
    void solve(TreeNode* root, int  x) {
        if(!root) return ;

        root->val = x ;
        st.insert(x);
        if(root->left) solve(root->left, 2*x+1);
        if(root->right) solve(root->right, 2*x+2);
    }
    FindElements(TreeNode* root) {
        if (!root) return;
        st.clear();

        int x = 0;
        solve(root, x);
        
    }
    // bool isPresent(TreeNode* root, int target) {
    //     if(!root) return false;

    //     if(root->val == target) return true;

    //     return isPresent(root->left, target) || isPresent(root->right, target); 
    // }
    bool find(int target) {

        // if(!root) return false;

        // if(root->val == target) return true;

        // return isPresent(root, target);

        return st.count(target) ;
        
    }
};

// without usign set and with BFS
class FindElements {
public:
    TreeNode* root;
    FindElements(TreeNode* root) {
        this->root = root;
        
        recover(root, 0) ;
        
    }
    void recover(TreeNode* root, int x) {
        if(!root) return;

        queue<TreeNode*> que ;
        root->val = x;
        que.push(root) ;

        while(!que.empty()) {
            TreeNode* curr = que.front();
            que.pop();

            if(curr->left) {
                curr->left->val = 2*curr->val+1;
                que.push(curr->left);
            }
            if(curr->right) {
                curr->right->val = 2*curr->val+2;
                que.push(curr->right);
            }
        }
    }

    bool isPresent(TreeNode* root, int target) {
        if(!root) return false;

        if(root->val == target) return true;

        return isPresent(root->left, target) || isPresent(root->right, target);
    }
    bool find(int target) {
        if(!root) return false;

        return isPresent(root, target) ;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */